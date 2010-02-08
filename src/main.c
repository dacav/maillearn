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
#include <stdio.h>
#include <stdlib.h>

#include <dacav.h>

int main (int argc, char **argv)
{
    mbox_err_t err;
    mbox_t *mbox;

    assert(argv > 1);
    err = mbox_new(argv[1], &mbox);
    if (err) {
        fprintf(stderr, "Mbox error: %s\n", mbox_strerr(err));
        exit(1);
    }

    mbox_parse(mbox);

    mbox_free(mbox);
    exit(0);
}
