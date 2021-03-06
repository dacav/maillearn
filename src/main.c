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
#include <unistd.h>

#include <dacav.h>

int main (int argc, char **argv)
{
    mbox_err_t err;
    mbox_t *mbox;
    mbox_mail_t *mail;

    assert(argc > 1);
    err = mbox_new(argv[1], &mbox);
    if (err) {
        fprintf(stderr, "Mbox error: %s\n", mbox_strerr(err));
        exit(1);
    }

    printf("Starting to get milk\n");
    while ((mail = mbox_next_mail (mbox)) != NULL) {
        const dlist_t *trace;
        diter_t *iter;

        printf("Is to [%s]\n", mbox_mail_getattr(mail, "To"));
        printf("Mail trace:\n");
        trace = mbox_mail_gettrace(mail);
        iter = dlist_iter_new((dlist_t **)&trace);
        while (diter_hasnext(iter)) {
            printf("\t%s\n", (char *)diter_next(iter));
        }
        dlist_iter_free(iter);
        printf("FOLLOWING TEXT\n");
        printf("%s\n", mbox_mail_getbody(mail));
        printf("END OF TEXT\n");
        mbox_mail_free(mail);
    }
    printf("LOL WUT?\n");

    mbox_free(mbox);

    exit(0);
}
