/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "Game.hpp"

// Project includes
#include "Log.hpp"

#include <common/Constants.hpp>
#include <common/Json.hpp>

// Convenience macro
#define SEND(packetHeader, ...) \
    send({{ Constants::Packet::header, packetHeader }, ##__VA_ARGS__ })

namespace CP = Constants::Packet;

Game::Game(QUrl const & serverUrl, QString const & name, bool autoMode)
    : _serverUrl { serverUrl }
    , _name      { name      }
    , _autoMode  { autoMode  }
{
    QObject::connect(&_socket, &QWebSocket::connected,
                     this,     &Game::onSocketConnected);
    QObject::connect(&_socket, &QWebSocket::disconnected,
                     this,     &Game::onSocketDisconnected);

    using SocketError = QAbstractSocket::SocketError;
    QObject::connect(&_socket, qOverload<SocketError>(&QWebSocket::error),
                     this,     &Game::onSocketError);

    QObject::connect(&_socket, &QWebSocket::binaryMessageReceived,
                     this,     &Game::onMessageReceived);
    QObject::connect(&_socket, &QWebSocket::textMessageReceived,
        [this] (QString const & str) { onMessageReceived(str.toUtf8()); });
}

void Game::start()
{
    _socket.open(_serverUrl);
}

void Game::onSocketConnected()
{
    LOG(Info, "Connection with the game server established");
    SEND(CP::identity, { CP::name, _name.isEmpty() ? QJsonValue() : _name });

    // First we need to receive the rules before asking for input
    onPacketReceived = &Game::onRulesPacketReceived;
}

void Game::onSocketDisconnected()
{
    if (_socket.closeCode() == QWebSocketProtocol::CloseCodeGoingAway)
        LOG(Info, "Game has finished");

    emit finished();
}

void Game::onSocketError(QAbstractSocket::SocketError error)
{
    if (error == QAbstractSocket::ConnectionRefusedError)
    {
        LOG(Critical, "Couldn't connect to game server on '%1'")
            .arg(_socket.requestUrl().toString());
    }
    else
    {
        LOG(Critical, "Socket error: ") << _socket.errorString();
        _socket.abort();
    }
}

void Game::onMessageReceived(QByteArray const & message)
{
    QJsonParseError error;
    auto const document = QJsonDocument::fromJson(message, &error);

    if (document.isNull())
    {
        LOG(Critical, "Failed to parse message: ") << error.errorString();
        return _socket.abort();
    }

    auto const packet = document.object();

    LOG(Info, "Recv: '%1' (%2 byte(s)):\n%3")
        .arg(packet[CP::header].toString()).arg(message.size())
        .arg(Json::prettify(document));

    (this->*onPacketReceived)(packet);
}

void Game::onRulesPacketReceived(QJsonObject const & packet)
{
    auto const header = packet[CP::header].toString();
    if (header != CP::rules)
    {
        LOG(Critical, "Packet '%1' was unexpected.").arg(header);
        _socket.abort();
        return;
    }

    // Do not check the rules again because we trust the server on the format

    auto const bounds = packet[CP::bounds].toString().split(',');
    _rules = std::make_unique<Rules const>(
        bounds[0].toInt(), bounds[1].toInt(), packet[CP::limit].toInt(-1));
    _attemptsLeft = _rules->maxAttempts;

    onPacketReceived = &Game::onAnswerPacketReceived;

    // We can start guessing now
    guess();
}

void Game::onAnswerPacketReceived(QJsonObject const & packet)
{
    auto const header = packet[CP::header].toString();
    if (header != CP::answer && header != CP::gameOver)
    {
        LOG(Critical, "Packet '%1' was unexpected.").arg(header);
        _socket.abort();
        return;
    }

    if (header == CP::gameOver)
    {
        LOG(Info, "Server says: you lost!");
//        onPacketReceived = &Game::onScorePacketReceived;
        return;
    }

    auto const answer = packet[CP::answer].toString();
    /**/ if (answer == CP::lower)
        LOG(Warning, "Server says: you guessed too high!");
    else if (answer == CP::higher)
        LOG(Warning, "Server says: you guessed too low!");
    else
    {
        LOG(Info, "Server says: you won!");
//        onPacketReceived = &Game::onScorePacketReceived;
        return;
    }

    if (_attemptsLeft == -1 || --_attemptsLeft > 0)
        guess();
}

void Game::send(QJsonObject const & message)
{
    if (_socket.state() != QAbstractSocket::ConnectedState)
        return;

    QJsonDocument const doc { message };

    auto const size = _socket.sendBinaryMessage(doc.toJson());
    LOG(Info, "Sent: '%1' (%2 bytes):\n%3")
        .arg(message[CP::header].toString()).arg(size).arg(Json::prettify(doc));
}

void Game::guess()
{
    static QTextStream cin { stdin }, cout { stdout };

    int number = 0;

    bool ok = false;
    while (!ok)
    {
        auto const prompt = QString("Guess a number [%1 ; %2] (attempts left: %3): ")
                            .arg(_rules->bounds.min).arg(_rules->bounds.max);

        if (_rules->maxAttempts == -1)
            cout << prompt.arg("unlimited") << flush;
        else
            cout << prompt.arg(_attemptsLeft) << flush;

        number = cin.readLine().toInt(&ok);
    }

    SEND(CP::guess, { CP::guess, number });
}
