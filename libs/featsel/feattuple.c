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
#include <dacav.h>
#include <assert.h>

#include <math.h>

#include "headers/datatypes.h"

static
feat_tuple_t *create_tuple (featsel_t *fs)
{
    register char *chunk;
    feat_tuple_t *ret;

    assert(chunk = malloc(sizeof(feat_tuple_t) +
                          fs->nfeats * sizeof(double)));
    ret = (feat_tuple_t *)chunk;
    chunk += sizeof(feat_tuple_t);
    ret->values = (double *)chunk;
    ret->size = fs->nfeats;

    return ret;
}

feat_tuple_t *featsel_analyze (featsel_t *fs, void *elem)
{
    feat_tuple_t *tuple = create_tuple(fs);
    diter_t *iter;
    double *vals;

    iter = dlist_iter_new(&fs->sels);
    vals = tuple->values;
    while (diter_hasnext(iter)) {
        feat_fun_t f = (feat_fun_t) diter_next(iter);
        *vals ++ = f(elem, fs->user);
    }
    dlist_iter_free(iter);

    return tuple;
}

void featsel_tuple_free (feat_tuple_t *t)
{
    free(t);
}

static inline
double square (double x)
{
    return x * x;
}

double distance (feat_tuple_t *max, feat_tuple_t *min)
{
    register unsigned i;
    double ret = 0;

    for (i = 0; i < min->size; i ++) {
        ret += square(min->values[i] - max->values[i]);
    }
    while (i < max->size) {
        ret += square(max->values[i]);
    }
    return sqrt(ret);
}

double featsel_tuple_distance (feat_tuple_t *t0, feat_tuple_t *t1)
{
    if (t0->size > t1->size)
        return distance(t0, t1);
    return distance(t1, t0);
}

