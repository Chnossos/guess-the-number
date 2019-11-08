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
#include "WebSocketServer.hpp"

// Qt includes
#include <QCoreApplication>

class Application : public QCoreApplication
{
public:
    Application(int & argc, char *argv[]);

public:
    auto run() -> decltype(exec());

public:
    static auto instance() {
        return static_cast<Application *>(QCoreApplication::instance());
    }
};

#undef qApp
#define qApp Application::instance()
