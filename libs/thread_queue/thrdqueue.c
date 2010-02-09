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

#include <dacav.h>

#define STATUS_ACTIVE 	0x00

#define STATUS_ABORTED  0x01
#define STATUS_ENDDATA  0x02
#define STMASK_NOINSERT 0x03

struct thrdqueue {
    dlist_t* list;          /* Storage buffer elements */

    pthread_cond_t empty;   /* Lock if queue is empty */
    pthread_mutex_t cmux;   /* Condition mutex */

	unsigned char status;
};

thrdqueue_t * thq_new ()
{
    thrdqueue_t *ret;

    assert(ret = malloc(sizeof(thrdqueue_t)));

    ret->list = dlist_new();
	ret->status = STATUS_ACTIVE;

    assert(pthread_cond_init(&ret->empty, NULL) == 0);
    assert(pthread_mutex_init(&ret->cmux, NULL) == 0);

    return ret;
}

thq_status_t thq_insert (thrdqueue_t *thq, void *el)
{
	register thq_status_t status;

    pthread_mutex_lock(&thq->cmux);
	status = thq->status;
    if (status & STMASK_NOINSERT) {
        pthread_mutex_unlock(&thq->cmux);
        return THQ_UNALLOWED;
    }
    thq->list = dlist_append(thq->list, el);
    pthread_mutex_unlock(&thq->cmux);
    pthread_cond_signal(&thq->empty);
    return THQ_SUCCESS;
}

thq_status_t thq_extract (thrdqueue_t *thq, void **el)
{
    register int status;
    register int empty;

    pthread_mutex_lock(&thq->cmux);
    while ((status = thq->status) != STATUS_ABORTED &&
		   (empty = dlist_empty(thq->list))) {
        pthread_cond_wait(&thq->empty, &thq->cmux);
    }
	if (!empty && status != STATUS_ABORTED) {
		thq->list = dlist_pop(thq->list, el);
	}
    pthread_mutex_unlock(&thq->cmux);

	if (status == STATUS_ABORTED)
		return THQ_ABORTED;
	if (empty && status == STATUS_ENDDATA) {
		return THQ_ENDDATA;
	}
	return THQ_SUCCESS;
}

void thq_abort (thrdqueue_t *thq)
{
    pthread_mutex_lock(&thq->cmux);
	thq->status = STATUS_ABORTED;
    pthread_mutex_unlock(&thq->cmux);

    pthread_cond_broadcast(&thq->empty);
}

void thq_delete (thrdqueue_t *thq, void (*memfree)(void *))
{
	dlist_free(thq->list, memfree);
    pthread_mutex_destroy(&thq->cmux);
    pthread_cond_destroy(&thq->empty);
    free(thq);
}

