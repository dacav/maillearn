/*
 * Copyright 2010 Giovanni Simoni
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

#include <featsel.h>
#include <assert.h>
#include <dacav.h>
#include "headers/datatypes.h"

featsel_t *featsel_new (void *user)
{
    register featsel_t *ret;

    assert(ret = malloc(sizeof(featsel_t)));
    ret->sels = dlist_new();
    ret->nfeats = 0;
    ret->user = user;

    return ret;
}

void featsel_add (featsel_t *fs, feat_fun_t f)
{
    fs->sels = dlist_append(fs->sels, f);
    fs->nfeats ++;
}

void featsel_free (featsel_t *fs)
{
    dlist_free(fs->sels, NULL);
}

