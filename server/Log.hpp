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
#include <QDebug>

#define LOG(level, id, message)      \
    q ## level().noquote().nospace() \
        << QString("[%1][%2] ").arg(id, 6).arg(#level, 8) << QString(message)
