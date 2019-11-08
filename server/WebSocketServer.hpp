/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#pragma once

// Project includes
#include "Rules.hpp"

// Qt includes
#include <QWebSocketServer>

class WebSocketServer : public QObject
{
    Q_OBJECT

private:
    QWebSocketServer _server;
    Rules const &    _rules;
    quint16          _port = 0;

public:
    WebSocketServer(quint16 port, Rules const & rules);

public:
    bool start();

private slots:
    void onNewConnection();
};
