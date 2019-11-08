/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "Client.hpp"

// Qt includes
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(unsigned int id, WebSocketPtr && socket)
    : _id     { id                                 }
    , _socket { std::forward<WebSocketPtr>(socket) }
{
    _socket->setParent(this);

    // Client shouldn't disconnect before we choose to kick him out
    QObject::connect(_socket.get(), &QWebSocket::disconnected,
                     this,          &Client::errorOccured);

    QObject::connect(_socket.get(), &QWebSocket::binaryMessageReceived,
                     this,          &Client::onMessageReceived);
    QObject::connect(_socket.get(), &QWebSocket::textMessageReceived,
        [this] (QString const & str) { onMessageReceived(str.toUtf8()); });
}

void Client::onMessageReceived(QByteArray const & message)
{
    QJsonParseError error;
    auto const document = QJsonDocument::fromJson(message, &error);

    if (document.isNull())
    {
        qCritical() << QString("[%1] Failed to parse message: ").arg(_id)
                    << error.errorString();

        emit errorOccured(); // Terminate the session
    }
    else
        emit packetReceived(document.object());
}
