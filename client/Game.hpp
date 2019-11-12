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
#include <common/Rules.hpp>

// Qt includes
#include <QJsonObject>
#include <QWebSocket>

// C++ includes
#include <memory>

class Game : public QObject
{
    Q_OBJECT

private:
    QWebSocket    _socket;
    QUrl const    _serverUrl;
    QString const _name;
    bool const    _autoMode;

    using RulesPtr = std::unique_ptr<Rules const>;
    RulesPtr      _rules;
    int           _attemptsLeft = -1;

public:
    Game(QUrl const & serverUrl, QString const & name, bool autoMode);

public:
    void start();

signals:
    void finished();

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onMessageReceived(QByteArray const & message);

private:
    // Let's do a simple State Machine to ease the error handling
    void (Game::*onPacketReceived)(QJsonObject const & packet);
    void onRulesPacketReceived(QJsonObject const & packet);
    void onAnswerPacketReceived(QJsonObject const & packet);
//    void onScorePacketReceived(QJsonObject const & packet);

private:
    void send(QJsonObject const & message);
    void guess();
};
