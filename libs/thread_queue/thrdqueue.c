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

#include <thrdqueue.h>

#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <dacav.h>

struct thrdqueue {
    dlist_t* list;          /* Storage buffer elements */

    pthread_cond_t empty;   /* Lock if queue is empty */
    pthread_mutex_t cmux;   /* Condition mutex */

    pthread_cond_t enddata; /* Lock until data is flushed */

    int active;
};

thrdqueue_t * thq_new ()
{
    thrdqueue_t *ret;

    assert(ret = malloc(sizeof(thrdqueue_t)));

    ret->list = dlist_new();
    ret->active = 1;

    assert(pthread_cond_init(&ret->empty, NULL) == 0);
    assert(pthread_cond_init(&ret->enddata, NULL) == 0);
    assert(pthread_mutex_init(&ret->cmux, NULL) == 0);

    return ret;
}

thq_status_t thq_insert (thrdqueue_t *thq, void *el)
{
	register thq_status_t ret;

    ret = THQ_ENDDATA;
    pthread_mutex_lock(&thq->cmux);
    if (thq->active) {
        thq->list = dlist_append(thq->list, el);
        ret = THQ_SUCCESS;
    }
    pthread_mutex_unlock(&thq->cmux);

    pthread_cond_signal(&thq->empty);
    return ret;
}

thq_status_t thq_extract (thrdqueue_t *thq, void **el)
{
    register unsigned active;
    register unsigned empty;

    pthread_mutex_lock(&thq->cmux);
    while ((active = thq->active) &&
           dlist_empty(thq->list)) {
        pthread_cond_wait(&thq->empty, &thq->cmux);
    }
    empty = dlist_empty(thq->list);
    if (!empty) {
        thq->list = dlist_pop(thq->list, el);
    }
    pthread_mutex_unlock(&thq->cmux);

    if (!active && empty) {
        pthread_cond_signal(&thq->enddata);
        return THQ_ENDDATA;
    }
    /* It was not empty */
    return THQ_SUCCESS;
}

void thq_delete (thrdqueue_t *thq, void (*memfree)(void *))
{
	dlist_free(thq->list, memfree);
    pthread_mutex_destroy(&thq->cmux);
    pthread_cond_destroy(&thq->empty);
    pthread_cond_destroy(&thq->enddata);
    free(thq);
}

void thq_enddata (thrdqueue_t *thq)
{
    pthread_mutex_lock(&thq->cmux);
    thq->active = 0;
    pthread_cond_signal(&thq->empty);
    while (!dlist_empty(thq->list)) {
        pthread_cond_wait(&thq->enddata, &thq->cmux);
    }
    pthread_mutex_unlock(&thq->cmux);
}

