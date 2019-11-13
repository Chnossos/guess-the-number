/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "Client.hpp"

// Project includes
#include "Log.hpp"

#include <common/Constants.hpp>

// Qt includes
#include <QJsonDocument>
#include <QJsonObject>

namespace CP = Constants::Packet;

Client::Client(unsigned int id, WebSocketPtr && socket)
    : _id     { id                                 }
    , _socket { std::forward<WebSocketPtr>(socket) }
{
    _socket->setParent(this);

    // Client shouldn't disconnect before we choose to kick him out
    QObject::connect(_socket.get(), &QWebSocket::disconnected,
                     this,          &Client::onSocketDisconnected);

    QObject::connect(_socket.get(), &QWebSocket::binaryMessageReceived,
                     this,          &Client::onMessageReceived);
    QObject::connect(_socket.get(), &QWebSocket::textMessageReceived,
        [this] (QString const & str) { onMessageReceived(str.toUtf8()); });
}

void Client::send(QString const & header, QJsonObject packet)
{
    packet.insert(CP::header, header);

    QJsonDocument const doc { packet };

    auto const size = _socket->sendBinaryMessage(doc.toJson());
    LOG(Info, _id, "Sent: '%1' (%2 bytes):\n%3")
        .arg(header).arg(size)
        .arg(QString(doc.toJson(QJsonDocument::Indented)).replace(QRegExp("\n$"), ""));
}

void Client::onSocketDisconnected()
{
    auto const closeReason = _socket->closeReason();
    if (closeReason.isEmpty())
        LOG(Warning, _id, "Player has left the game");
    else
        LOG(Warning, _id, "Player has left the game (%1)").arg(closeReason);
}

void Client::onMessageReceived(QByteArray const & message)
{
    QJsonParseError error;
    auto const document = QJsonDocument::fromJson(message, &error);

    if (document.isNull())
    {
        LOG(Critical, _id, "Failed to parse message: ") << error.errorString();
        emit errorOccured(); // Terminate the session
    }
    else
    {
        auto const packet = document.object();

        LOG(Info, _id, "Recv: '%1' (%2 bytes):\n%3")
            .arg(packet[CP::header].toString()).arg(message.size())
            .arg(QString(document.toJson(QJsonDocument::Indented)));

        emit packetReceived(packet);
    }
}
