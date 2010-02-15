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

#ifndef __defined_datatypes_h
#define __defined_datatypes_h

#include <dacav.h>
#include <featsel.h>

struct featsel {
    dlist_t *sels;      /* List of feature selection functions */
    size_t nfeats;      /* Number of features */
    void *user;         /* Private user data */
};

struct feat_tuple {
    double *values;     /* Array of values */
    size_t size;        /* Size of the array */
};

#endif // __defined_datatypes_h

