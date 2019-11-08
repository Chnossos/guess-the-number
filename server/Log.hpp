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

#define LOG(level, id) \
    q ## level().noquote().nospace() << QString("[%1] ").arg(id, 6)
