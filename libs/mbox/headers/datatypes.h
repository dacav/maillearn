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
    dhash_t *fields;
    dstrbuf_t *body;
    // TODO mail protection with mutex
};

typedef struct {
    regex_t field;              /* Field splitting regex */
    dhash_t *keys;              /* Keys used in mail objects */
    pthread_mutex_t mx;         /* Protect keys hash */
} parse_t;

/* Typedef'd on mbox_t */
struct mbox {
    FILE *file;                 /* mbox file to be read */
    parse_t parse;              /* Parsing data */
    thrdqueue_t *mail_queue;    /* Queue of outgoing mails */
    pthread_t parser_th;        /* Parsing thread */

    /* Auxiliary data, for internal use, during the parsing phase */
    struct {
        char *key;              /* Name of the field */
        dstrbuf_t *multiline;   /* For multilined values */
    } aux;
};

#endif // __defined_datatypes_h
