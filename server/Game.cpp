/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "Game.hpp"

// Project include
#include "Log.hpp"

#include <common/Constants.hpp>

// Qt includes
#include <QRandomGenerator>

// C++ includes
#include <random>

#include <QJsonDocument>

namespace CP = Constants::Packet;

namespace
{
    int rand(int min, int max)
    {
        std::uniform_int_distribution<int> distribution { min, max };
        return distribution(*QRandomGenerator::global());
    }
} // !namespace

Game::Game(unsigned int id, WebSocketPtr && socket,
           Rules const & rules, QObject * parent)
    : QObject       { parent                                   }
    , _id           { id                                       }
    , _client       { id, std::forward<WebSocketPtr>(socket)   }
    , _rules        { rules                                    }
    , _number       { rand(rules.bounds.min, rules.bounds.max) }
    , _attemptsLeft { rules.maxAttempts                        }
{
    QObject::connect(&_client, &Client::packetReceived,
                     this,     &Game::onPacketReceived);

    auto const msg = QString("Game has started: Number is %1, %2 attempt%3")
                     .arg(_number);

    if (_attemptsLeft == -1)
        LOG(Info, _id, msg).arg("unlimited").arg('s');
    else
        LOG(Info, _id, msg).arg(_attemptsLeft).arg(_attemptsLeft != 1 ? "s": "");

    handlePacket = &Game::handleIdentityPacket;
}

void Game::onPacketReceived(QJsonObject const & packet)
{
    LOG(Info, _id, "Received packet '%1':\n%2").arg(packet[CP::header].toString())
        .arg(QString(QJsonDocument(packet).toJson(QJsonDocument::Indented)));

    (this->*handlePacket)(packet);
}

void Game::handleIdentityPacket(QJsonObject const & packet)
{
    auto const header = packet[CP::header].toString();
    if (header != CP::identity)
    {
        LOG(Critical, _id, "Packet '%1' was unexpected!").arg(header);
        emit finished();
        return;
    }

    if (!packet[CP::name].isNull())
        _name = packet[CP::name].toString();

    // Send the rules so the player can get started
    auto const & bounds = _rules.bounds;
    _client.send(CP::rules, {
        { CP::bounds, QString("%1,%2").arg(bounds.min).arg(bounds.max)             },
        { CP::limit,  _rules.maxAttempts == -1 ? QJsonValue() : _rules.maxAttempts }
    });

    handlePacket = &Game::handleGuessPacket;
}

void Game::handleGuessPacket(QJsonObject const & packet)
{
    auto const header = packet[CP::header].toString();
    if (header != CP::guess)
        LOG(Critical, _id, "Packet '%1' was unexpected!").arg(header);
    else if (!packet[CP::guess].isDouble())
    {
        LOG(Critical, _id,
            "Malformed packet: field '%1' is not a number").arg(CP::guess);
    }
    else
    {
        if (_attemptsLeft != -1)
            --_attemptsLeft;

        int const guess = packet[CP::guess].toInt();
        /**/ if (guess > _number)
            _client.send(CP::answer, {{ CP::answer, CP::lower  }});
        else if (guess < _number)
            _client.send(CP::answer, {{ CP::answer, CP::higher }});
        else
            _client.send(CP::answer, {{ CP::answer, CP::equals }});

        if (guess != _number) return;
        // TODO: Save score if not anonymous (always anonymous in auto-mode)
//        if (guess == _number && !_name.isEmpty())
//            saveScore(_name, _number, _attemptsLeft);
//        else
//            return;
    }
    emit finished();
}
