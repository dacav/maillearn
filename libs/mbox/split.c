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

#include <mbox.h>

#include "headers/datatypes.h"
#include "headers/strings.h"
#include "headers/parse.h"
#include "headers/mail.h"

#include <regex.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <thrdqueue.h>

/* Enqueues a mail object. If the operationg gets aborted by any other
 * thread, every element gets extracted and freed.
 */
static
int enqueue_mail (mbox_t *mbox, mbox_mail_t *mail)
{
    register thrdqueue_t *q = mbox->mail_queue;

    if (thq_insert(q, (void *)mail) == THQ_UNALLOWED) {
        /* There has been an abort! Dispatch the exit signal! */
        return 1;
    }
    return 0;
}

static inline
int match_mailstart (regex_t *reg, parse_t *p, const char *str)
{
    return regexec(reg, str, 0, NULL, 0) != REG_NOMATCH;
}

int split_start (mbox_t *mbox)
{
    size_t n;
    ssize_t len;
    char *line = NULL;
    mbox_mail_t *mail = NULL;
    register parse_t *p = &mbox->parse;
    regex_t mailstart_re;

    assert(!regcomp(&mailstart_re, "^From .*$", REG_NOSUB | REG_EXTENDED));

    while ((len = getline(&line, &n, mbox->file)) >= 0) {
        line[len - 1] = 0;  /* Remove trailing \n */

        /* If we have found a 'From ' line we start a new mail (and
         * enqueue the previous one
         */
        if (match_mailstart(&mailstart_re, p, line)) {
            if (mail) {
                if (enqueue_mail(mbox, mail)) {
                    /* Abort request, break cycle */
                    break;
                }
            }
            mail = mail_new();
            continue;
        }

        /* This conditional will skip any row not belonging to a mail
         * (this should never happen though).
         */
        if (mail != NULL) {
            mail_append(mbox, mail, line);
        }
    }

    if (line) free(line);
    if (feof(mbox->file)) {
        if (mail) {
            enqueue_mail(mbox, mail);
        }
        thq_enddata(mbox->mail_queue);
        return 0;
    } else {
        return 1;
    }
}
