/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#include "Application.hpp"

// Qt includes
#include <QFileInfo>

Application::Application(int & argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    setApplicationName(QFileInfo(argv[0]).fileName());
}

auto Application::run() -> decltype(exec())
{
    Rules const rules { 1, 100, -1 }; // TODO: init from CmdLineParser

    WebSocketServer server { 4242, rules };
    return server.start() ? exec() : EXIT_FAILURE;
}
