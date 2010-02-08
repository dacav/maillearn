/*
 * Copyright 2009 2010 Giovanni Simoni
 *
 * This file is part of maillearn.
 *
 * maillearn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * maillearn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with maillearn.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "strings.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

unsigned long string_hash (const unsigned char *name)
{
    unsigned long h = 0, g;
    while (*name) {
        h = (h << 4) + *name++;
        if ((g = h & 0xf0000000) != 0) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h;
}

char *string_alloc (char *orig, size_t len)
{
    register char *ret;

    if (len == 0) {
        len = strlen(orig);
    }
    assert(ret = malloc(len * sizeof(char)));
    strncpy(ret, orig, len);
    return ret;
}

