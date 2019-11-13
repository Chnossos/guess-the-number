/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/13
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#pragma once

// Qt includes
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegExp>
#include <QString>

namespace Json
{
    inline QString prettify(QJsonDocument const & doc)
    {
        return QString(doc.toJson(QJsonDocument::Indented))
                .replace(QRegExp("\n$"), "");
    }
} // !namespace Json
