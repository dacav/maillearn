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

struct thrdqueue {
    dlist_t* list;         /* Storage buffer elements */

    pthread_cond_t empty;   /* Lock if queue is empty */
    pthread_mutex_t cmux;   /* Condition mutex */

    int abort;

};

thrdqueue_t * thq_new ()
{
    thrdqueue_t *ret;

    assert(ret = malloc(sizeof(thrdqueue_t)));

    assert(pthread_cond_init(&ret->empty, NULL) == 0);
    assert(pthread_mutex_init(&ret->cmux, NULL) == 0);
    ret->list = dlist_new();
    ret->abort = 0;

    return ret;
}

int thq_insert (thrdqueue_t *thq, void *el)
{
    pthread_mutex_lock(&thq->cmux);
    if (thq->abort) {
        pthread_mutex_unlock(&thq->cmux);
        return 1;
    }
    thq->list = dlist_append(thq->list, el);
    pthread_mutex_unlock(&thq->cmux);

    pthread_cond_signal(&thq->empty);

    return 0;
}

int thq_extract (thrdqueue_t *thq, void **el)
{
    register int abort;

    pthread_mutex_lock(&thq->cmux);
    while (dlist_empty(thq->list) && !thq->abort) {
        pthread_cond_wait(&thq->empty, &thq->cmux);
    }
    abort = thq->abort;
    if (!abort) {
        thq->list = dlist_pop(thq->list, el);
    }
    pthread_mutex_unlock(&thq->cmux);

    return abort;
}

int thq_extract_nowait (thrdqueue_t *thq, void **el)
{
	register int ret;
	register dlist_t *lst;

    pthread_mutex_lock(&thq->cmux);
	lst = thq->list;
	if (dlist_empty(lst)) {
		ret = 1;
	} else {
		thq->list = dlist_pop(lst, el);
		ret = 0;
	}
    pthread_mutex_unlock(&thq->cmux);

	return ret;
}

void thq_delete (thrdqueue_t *thq)
{
    pthread_mutex_destroy(&thq->cmux);
    pthread_cond_destroy(&thq->empty);
    free(thq);
}

void thq_abort (thrdqueue_t *thq)
{
    pthread_mutex_lock(&thq->cmux);
    thq->abort = 1;
    pthread_mutex_unlock(&thq->cmux);
    pthread_cond_broadcast(&thq->empty);
}

