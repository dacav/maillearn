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

#include <stdio.h>
#include <regex.h>
#include <pthread.h>

#include <dacav.h>
#include <thrdqueue.h>

struct mbox_mail {
    dlist_t *trace;             /* Sequence of trace fields */
    dhash_t *fields;            /* Generic fields */

    /* About body lines extraction:
     *      body        is used during mail construction;
     *      body_str    is constructed at the first reading (while body
     *                  is cleaned and setted to null.
     */
    dstrbuf_t *body;            /* Body lines */
    const char *body_str;       /* Body lines extracted */
    // TODO mail protection with mutex

    mbox_t *mbox;               /* Pointer to mailbox */
};

typedef struct {
    dhash_t *keys;              /* Keys used in mail objects */
    pthread_mutex_t mx;         /* Protect keys hash */

    regex_t trace;              /* Trace field regex */
    regex_t field;              /* Generic field regex */
} parse_t;

/* Typedef'd on mbox_t */
struct mbox {
    FILE *file;                 /* mbox file to be read */
    parse_t parse;              /* Parsing data */
    thrdqueue_t *mail_queue;    /* Queue of outgoing mails */
    pthread_t parser_th;        /* Parsing thread */

    /* Auxiliary data, for internal use, during the parsing phase */
    struct {
        enum {
           STATUS_NODATA,       /* Not recording */
           STATUS_TRACE,        /* Recording a trace field */
           STATUS_FIELD         /* Recording a generic field */
        } status;
        char *key;              /* Name of the field */
        dstrbuf_t *multiline;   /* For multilined values */
    } aux;
};

#endif // __defined_datatypes_h

