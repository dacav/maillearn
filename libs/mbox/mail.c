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

#include "headers/datatypes.h"
#include "headers/strings.h"
#include "headers/parse.h"

#include <dacav.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAIL_HASH_SIZE 5

mbox_mail_t * mail_new ()
{
    mbox_mail_t *ret;

    assert(ret = malloc(sizeof(mbox_mail_t)));
    ret->fields = dhash_new(MAIL_HASH_SIZE, (dhash_func_t)string_hash,
                                            (dcmp_func_t)strcmp);
    return ret;
}

void mail_free (mbox_mail_t *mail)
{
    dhash_free(mail->fields, NULL, free);
	free(mail);
}

void mail_append (mbox_t *mbox, mbox_mail_t *mail, char *row)
{
    char *key, *value;

#if 0
    if (isspace(row[0])) {
        /* Append to old field or ignore if there's no such field. */
    } else {
        /* Create a new field */
    }
#endif
    // TODO FIX HERE

    if (parse_match(&mbox->parse, row, &key, &value)) {
        dhash_insert(mail->fields, (void *)key, (void *)value);
    } else {
    }
}

#if 0

            if (!isspace(line[0])) {
                regmatch_t match[2];
                s = string_alloc(line, len);

                /* A new logical line, select a possible setter, default
                 * is mail_append */
                setter = NULL;
                if (match_from(p, line, match)) {
                    setter = mail_set_from;
                } else if (match_to(p, line, match)) {
                    setter = mail_set_to;
                } else if (match_subject(p, line, match)) {
                    setter = mail_set_subject;
                }
            } else {
                s = string_alloc(line + 1, len - 1);
                /* This belongs to the previous logical line, we keep
                 * using the previous setter */
            }
            mail_append(mail, s);
            if (setter) setter(mail, s);

#endif



#if 0
void mail_set_from (mail_t *mail, const char *from)
{
	mail->from = dlist_append(mail->from, (void *)from);
}

void mail_set_to (mail_t *mail, const char *to)
{
	mail->to = dlist_append(mail->to, (void *)to);
}

void mail_set_subject (mail_t *mail, const char *subject)
{
	mail->subject = dlist_append(mail->subject, (void *)subject);
}

void mail_append (mail_t *mail, const char *row)
{
	mail->rows = dlist_append(mail->rows, (void *)row);
}
#endif

