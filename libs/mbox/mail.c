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

mbox_mail_t * mail_new (mbox_t *mbox)
{
    mbox_mail_t *ret;

    assert(ret = malloc(sizeof(mbox_mail_t)));
    ret->trace = dlist_new();
    /* NOTE: the fields works directly with addresses as key thanks to the
     *       parse_t::keys hash table. */
    ret->fields = dhash_new(MAIL_HASH_SIZE, NULL, NULL);
    ret->body = dstrbuf_new("\n", 1);
    ret->body_str = NULL;
    ret->mbox = mbox;

    return ret;
}

void mbox_mail_free (mbox_mail_t *mail)
{
    dhash_free(mail->fields, NULL, free);
    if (mail->body) {
        /* If the mail text has not been read yet */
        dstrbuf_free(mail->body);
    }

    /* Note: this may be null, but this is not a problem for free */
    free((void *)(mail->body_str));

	free(mail);
}

void mail_body_append (mbox_t *mbox, mbox_mail_t *mail, char *row,
                       size_t rowlen)
{
    dstrbuf_insert(mail->body, row, rowlen);
}

void mail_header_end (mbox_t *mbox, mbox_mail_t *mail)
{
    register int status = mbox->aux.status;
    register char *lines;

    if (status == STATUS_NODATA) return;
    lines = dstrbuf_extract(mbox->aux.multiline);
    if (status == STATUS_FIELD && mbox->aux.key != NULL) {
        /* Registering a field */
        dhash_insert(mail->fields, mbox->aux.key, lines);
    } else if (status == STATUS_TRACE) {
        /* Append */
        mail->trace = dlist_append(mail->trace, lines);
    } else {
        /* This should never happen. */
        free(lines);
        abort();    // TODO remove this, eventually.
    }
    mbox->aux.key = NULL;
    mbox->aux.status = STATUS_NODATA;
}

void mail_header_append (mbox_t *mbox, mbox_mail_t *mail, char *row,
                         size_t rowlen)
{
    char *key, *value;

    if (isspace(row[0]) && mbox->aux.status != STATUS_NODATA) {
        /* Part of a previous header */
        dstrbuf_insert(mbox->aux.multiline, row, rowlen);
    } else {
        mail_header_end(mbox, mail);    // store any previous open header.
        if (parse_trace(&mbox->parse, row, &value)) {
            /* A new trace field */
            mbox->aux.status = STATUS_TRACE;
        } else if (parse_field(&mbox->parse, row, &key, &value)) {
            /* A new generic field */
            mbox->aux.key = key;
            mbox->aux.status = STATUS_FIELD;
        }
        dstrbuf_insert(mbox->aux.multiline, value, 0);
    }
    /* Any other line is considered garbage. */
}

const char *mbox_mail_getattr (mbox_mail_t *mail, const char *key)
{
    const char *ret;
    void *address;
    register mbox_t *mbox = mail->mbox;

    pthread_mutex_lock(&mbox->parse.mx);
    if (dhash_search(mbox->parse.keys, key, &address) ==
            DHASH_NOTFOUND) {
        address = NULL;
    }
    pthread_mutex_unlock(&mbox->parse.mx);
    if (address != NULL) {
        if (dhash_search(mail->fields, address, (void **)&ret) ==
                DHASH_NOTFOUND)
            return NULL;
        return ret;
    }
    return NULL;
}

const dlist_t *mbox_mail_gettrace (mbox_mail_t *mbox)
{
    return (const dlist_t *)(mbox->trace);
}

const char *mbox_mail_getbody (mbox_mail_t *mail)
{
    register const char *body_str = mail->body_str;

    if (body_str == NULL) {
        body_str = dstrbuf_extract(mail->body);
        mail->body_str = body_str;
        dstrbuf_free(mail->body);
        mail->body = NULL;
    }
    return body_str;
}

