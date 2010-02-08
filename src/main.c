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

#include <dacav.h>

int main (int argc, char **argv)
{
    mbox_t *mbox;
    mbox_err_t error;
    diter_t *it;

    assert(argc >= 2);
    error = mbox_map_file(argv[1], &mbox);
    if (error != MBOX_SUCCESS) {
        fprintf(stderr, mbox_strerror(error));
        exit(1);
    }
    mbox_bookmark(mbox);

    it = dlist_iter_new(&mbox->bookmarks);
    while (diter_hasnext(it)) {
        mbox_mail_t *mail = (mbox_mail_t *)diter_next(it);
        printf("start=%d len=%d\n", (int)(mail->start), mail->length);
    }
    dlist_iter_free(it);

    mbox_release_file(mbox);

    exit(0);
}

