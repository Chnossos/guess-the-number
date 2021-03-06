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

#include <common/Rules.hpp>

// Qt includes
#include <QObject>

class Game : public QObject
{
    Q_OBJECT

private:
    unsigned int const _id;
    Client             _client;
    Rules const &      _rules;
    QString            _name;
    int                _number;
    int                _attemptsLeft;

public:
    Game(unsigned int id, WebSocketPtr && socket,
         Rules const & rules, QObject * parent);

signals:
    void finished();

private slots:
    void onPacketReceived(QJsonObject const & packet);

private:
    void (Game::*handlePacket)(QJsonObject const & packet);
    void handleIdentityPacket(QJsonObject const & packet);
    void handleGuessPacket(QJsonObject const & packet);
};
