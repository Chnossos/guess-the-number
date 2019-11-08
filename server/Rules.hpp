/*
** Copyright 2019 Vivoka
**
** Made by Pierre Caissial on 2019/11/8
** Mail <pierre.caissial@vivoka.com>
**
** vivoka.com
*/

#pragma once

struct Rules
{
    struct Bounds { int min = 1; int max = 100; } const bounds;
    int const maxAttempts = -1;

    Rules(int boundsMin, int boundsMax, int maxAttempts)
        : bounds      { boundsMin, boundsMax }
        , maxAttempts { maxAttempts          }
    {}
};
