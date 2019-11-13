/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/12
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#pragma once

// Convenience macros
#define KEY_VALUE(key, value) constexpr auto const key = value
#define KEY(key)              KEY_VALUE(key, #key)

namespace Constants
{
    namespace Packet
    {
        KEY(answer);
        KEY(attempts);
        KEY(bounds);
        KEY(guess);
        KEY(header);
        KEY(identity);
        KEY(limit);
        KEY(name);
        KEY(rules);
        KEY(score);

        KEY_VALUE(elapsedTime, "elapsed_time");
        KEY_VALUE(gameOver,    "game_over");
        KEY_VALUE(equals,      "=");
        KEY_VALUE(higher,      "+");
        KEY_VALUE(lower,       "-");
    } // !namespace Packet
} // !namespace Constants

// Do not pollute the global space
#undef KEY
#undef KEY_VALUE
