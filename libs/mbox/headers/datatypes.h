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
#include <sys/types.h>
#include <regex.h>
#include <pthread.h>

#include <dacav.h>
#include <thrdqueue.h>

/* Managed by the private mail.c module. */
typedef struct {
    dlist_t * from;
    dlist_t * to;
    dlist_t * subject;

    dlist_t * rows;
} mail_t;

/* Managed by the parse.c module. */
typedef struct {
    regex_t mailstart;      /* Starting of mail */
    regex_t fld_from;       /* From field */
    regex_t fld_to;         /* To field */
    regex_t fld_subject;    /* Subject field */
} parse_t;

struct mbox {
    FILE *file;                 /* mbox file to be read */
    parse_t parse;              /* Parsing data */
    thrdqueue_t *mail_queue;    /* Queue of outgoing mails */
    pthread_t parser;           /* Parsing thread */
};

#endif // __defined_datatypes_h
