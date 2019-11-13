/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#pragma once

// Qt includes
#include <QJsonObject>
#include <QWebSocket>

// C++ includes
#include <memory>

using WebSocketPtr = std::unique_ptr<QWebSocket>;

class Client : public QObject
{
    Q_OBJECT

private:
    unsigned int const _id;
    WebSocketPtr const _socket;

public:
    Client(unsigned int id, WebSocketPtr && socket);

public:
    void send(QString const & header, QJsonObject packet = {});

signals:
    void errorOccured();
    void packetReceived(QJsonObject const & packet);

private slots:
    void onSocketDisconnected();
    void onMessageReceived(QByteArray const & message);
};
