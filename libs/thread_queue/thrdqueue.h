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

#ifndef __defined_thrdqueue_h
#define __defined_thrdqueue_h

#include <stdlib.h>

/* FIFO multithreaded queue */
typedef struct thrdqueue thrdqueue_t;

/* Initializes a new queue of len elements */
thrdqueue_t * thq_new ();

typedef enum {
    THQ_SUCCESS = 0,         /* Normally working */
    THQ_UNALLOWED,           /* Operation not allowed */
    THQ_ABORTED,             /* Operation aborted */
    THQ_ENDDATA
} thq_status_t;

/* Try to extract the oldest element.
 *
 * - Locks if there are no elements for the moment;
 * - Returns THQ_ENDDATA if there won't be any other element (thq_enddata
 *                      called by the producer);
 * - Returns THQ_SUCCESS if the extraction has been achieved;
 * - Returns THQ_ABORTED if the queue operation has been aborted.
 */
thq_status_t thq_extract (thrdqueue_t *thq, void **el);

/* Try to insert an element.
 *
 * - Returns THQ_UNALLOWED if the queue has been aborted (thq_abort has
 *                        been called) or if there won't be any other
 *                        element (thq_enddata has been called);
 * - Returns THQ_SUCCESS on success.
 */
thq_status_t thq_insert (thrdqueue_t *thq, void *el);

/* Forces all waiting processes to return, leaving any element enqueued.
 *
 * In order to remove elements, use the thq_delete procedure.
 */
void thq_abort (thrdqueue_t *thq);

/* Signals the end of data.
 *
 * This function locks until every element of the queue has been flushed
 * or thq_abort() has been called.
 */
void thq_enddata (thrdqueue_t *thq);

/* Deletes a queue and frees all stored elements.
 *
 * Note: this should be achieved only if safe on the threading point of
 *       view, otherwise it may lead to unpredictable behaviors.
 */
void thq_delete (thrdqueue_t *thq, void (*memfree)(void *));

#endif // __defined_thrdqueue_h
