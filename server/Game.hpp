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
#include "Client.hpp"
#include "Rules.hpp"

// Qt includes
#include <QObject>

class Game : public QObject
{
    Q_OBJECT

private:
    unsigned int const _id;
    Client             _client;
    Rules const &      _rules;

public:
    Game(unsigned int id, WebSocketPtr && socket,
         Rules const & rules, QObject * parent);

signals:
    void finished();

private slots:
    void onPacketReceived(QJsonObject const & packet);
};
