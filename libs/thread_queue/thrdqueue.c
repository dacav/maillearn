/*

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For a copy of GNU General Public License see
    <http://www.gnu.org/licenses/>.

*/

#include <thrdqueue.h>

#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

struct thrdqueue {

    struct {
        void ** elems;      /* Storage buffer elements */
        size_t length;      /* Storage buffer length */
    } buffer;

    unsigned first;         /* First available cell */
    size_t used;            /* Number of used cells */

    pthread_cond_t empty;   /* Lock if queue is empty */
    pthread_cond_t full;    /* Lock if queue is full */

    pthread_mutex_t cmux;   /* Condition mutex */
    pthread_mutex_t bmux;   /* Buffer mutex */

    int abort;

};

thrdqueue_t * thq_new (size_t len)
{
    thrdqueue_t *ret = malloc(sizeof(thrdqueue_t) + len * sizeof(void *));
    assert(ret != NULL);

    assert(pthread_cond_init(&ret->empty, NULL) == 0);
    assert(pthread_cond_init(&ret->full, NULL) == 0);

    assert(pthread_mutex_init(&ret->cmux, NULL) == 0);
    assert(pthread_mutex_init(&ret->bmux, NULL) == 0);

    ret->buffer.elems = (void **)((char *)ret + sizeof(thrdqueue_t));
    ret->buffer.length = len;
    ret->used = ret->first = 0;
    ret->abort = 0;

    return ret;
}

int thq_insert (thrdqueue_t *thq, void *el)
{
    register size_t first;
    register int abort;

    pthread_mutex_lock(&thq->cmux);
    while (thq->used >= thq->buffer.length && !thq->abort) {
        pthread_cond_wait(&thq->full, &thq->cmux);
    }
    thq->used ++;
    abort = thq->abort;
    pthread_mutex_unlock(&thq->cmux);

    if (abort)
        return 1;

    pthread_mutex_lock(&thq->bmux);
    first = thq->first;
    thq->buffer.elems[first ++] = el;
    thq->first = first % thq->buffer.length;
    pthread_mutex_unlock(&thq->bmux);

    pthread_cond_signal(&thq->empty);

    return 0;
}

int thq_extract (thrdqueue_t *thq, void **el)
{
    register size_t last;
    register int abort;
    void *retval;

    pthread_mutex_lock(&thq->cmux);
    while (thq->used <= 0 && !thq->abort) {
        pthread_cond_wait(&thq->empty, &thq->cmux);
    }
    abort = thq->abort;
    last = -- thq->used;
    pthread_mutex_unlock(&thq->cmux);

    if (abort)
        return 1;

    pthread_mutex_lock(&thq->bmux);
    last += thq->first - 1;
    retval = thq->buffer.elems[last % thq->buffer.length];
    pthread_mutex_unlock(&thq->bmux);

    pthread_cond_signal(&thq->full);

    *el = retval;
    return 0;
}

void thq_delete (thrdqueue_t *thq)
{
    pthread_mutex_destroy(&thq->cmux);
    pthread_mutex_destroy(&thq->bmux);
    pthread_cond_destroy(&thq->empty);
    pthread_cond_destroy(&thq->full);
    free(thq);
}

void thq_abort (thrdqueue_t *thq)
{
    pthread_mutex_lock(&thq->cmux);
    thq->abort = 1;
    pthread_mutex_unlock(&thq->cmux);
    pthread_cond_broadcast(&thq->empty);
    pthread_cond_broadcast(&thq->full);
}

