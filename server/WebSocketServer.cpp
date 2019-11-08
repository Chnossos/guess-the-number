/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "WebSocketServer.hpp"

// Project includes
#include "Application.hpp"
#include "Game.hpp"
#include "Log.hpp"

WebSocketServer::WebSocketServer(quint16 port, Rules const & rules)
    : _server { qApp->applicationName(), QWebSocketServer::NonSecureMode }
    , _rules  { rules                                                    }
    , _port   { port                                                     }
{
    QObject::connect(&_server, &QWebSocketServer::newConnection,
                     this,     &WebSocketServer::onNewConnection);
}

void WebSocketServer::onNewConnection()
{
    WebSocketPtr socket { _server.nextPendingConnection() };

    static unsigned int id = 0;
    auto const game        = new Game(++id, std::move(socket), _rules, &_server);

    QObject::connect(game, &Game::finished, game, &Game::deleteLater);
}

bool WebSocketServer::start()
{
    auto const success = _server.listen(QHostAddress::Any, _port);

    if (success)
        LOG(Info, "Server") << "Listening on *:" << _port;
    else
    {
        LOG(Warning, "Server") << "Could not listen to incomming connections: "
                               << _server.errorString();
    }

    return success;
}
