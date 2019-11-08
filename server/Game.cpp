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

Game::Game(unsigned int id, WebSocketPtr && socket,
           Rules const & rules, QObject * parent)
    : QObject { parent                                 }
    , _id     { id                                     }
    , _client { id, std::forward<WebSocketPtr>(socket) }
    , _rules  { rules                                  }
{
    QObject::connect(&_client, &Client::packetReceived,
                     this,     &Game::onPacketReceived);

    LOG(Info, id) << "Game has started!";
}

void Game::onPacketReceived(QJsonObject const &)
{
    // TODO: parse packet
}
