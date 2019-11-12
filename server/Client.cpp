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
    packet.insert(Constants::Packet::header, header);
    _socket->sendBinaryMessage(QJsonDocument(packet).toJson());
    LOG(Info, _id, "Sent packet '%1'").arg(header);
}

void Client::onSocketDisconnected()
{
    LOG(Warning, _id, "Player has left the game (%1)").arg(_socket->closeReason());
}

void Client::onMessageReceived(QByteArray const & message)
{
    QJsonParseError error;
    auto const document = QJsonDocument::fromJson(message, &error);

    if (document.isNull())
    {
        LOG(Critical, _id, "Failed to parse message: %1").arg(error.errorString());
        emit errorOccured(); // Terminate the session
    }
    else
        emit packetReceived(document.object());
}
