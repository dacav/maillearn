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
};

typedef struct {
    regex_t field;              /* Field splitting regex */
    dhash_t *keys;              /* Keys used in mail objects */

    dlist_t *accumulator;       /* Accumulator for multiple lines */
} parse_t;

/* Typedef'd on mbox_t */
struct mbox {
    FILE *file;                 /* mbox file to be read */
    parse_t parse;              /* Parsing data */
    thrdqueue_t *mail_queue;    /* Queue of outgoing mails */
    pthread_t parser_th;        /* Parsing thread */
};

#endif // __defined_datatypes_h
