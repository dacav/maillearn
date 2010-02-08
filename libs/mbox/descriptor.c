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

#include <mbox.h>

#include <assert.h>

#include "datatypes.h"

mbox_err_t mbox_new (const char *filename, mbox_t **mbox)
{
    mbox_t *ret;
    assert(ret = malloc(sizeof(mbox_t)));

    if ((ret->file = fopen(filename, "rt")) == NULL) {
        return MBOX_OPENING;
    }

    *mbox = ret;
    return MBOX_SUCCESS;
}

void mbox_free (mbox_t *mbox)
{
    fclose(mbox->file);
    free(ret);
}

