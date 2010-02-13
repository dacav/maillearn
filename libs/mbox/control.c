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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <thrdqueue.h>

#include "headers/datatypes.h"
#include "headers/parse.h"
#include "headers/mail.h"
#include "headers/split.h"

static
void * parsing_thread (void *arg)
{
    return (void *)split_start((mbox_t *)arg);
}

mbox_err_t mbox_new (const char *filename, mbox_t **mbox)
{
    register mbox_t *ret;
    assert(ret = malloc(sizeof(mbox_t)));

    if ((ret->file = fopen(filename, "rt")) == NULL) {
        return MBOX_OPENING;
    }
    ret->mail_queue = thq_new();
    parse_init(&ret->parse);
    ret->aux.key = NULL;
    ret->aux.multiline = dstrbuf_new("\n", 1);

    *mbox = ret;

    /* Starting thread */
    assert(pthread_create(&ret->parser_th, NULL, parsing_thread,
           (void *)ret) == 0);

    return MBOX_SUCCESS;
}

void mbox_free (mbox_t *mbox)
{
    register thrdqueue_t *q = mbox->mail_queue;

    /* Join with thread */
    pthread_join(mbox->parser_th, NULL);

    thq_delete(q, (void (*)(void *))mbox_mail_free);
    parse_free(&mbox->parse);
    dstrbuf_free(mbox->aux.multiline);

    free(mbox);
}

