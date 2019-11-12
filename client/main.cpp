/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

// Qt includes
#include <QCoreApplication>
#include <QWebSocket>

#include "Game.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app { argc, argv };

    Game game {{ "ws://localhost:4242" }, {}, false };

    QObject::connect(&game, &Game::finished, &app, &QCoreApplication::quit);

    game.start();

    return app.exec();
}
