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

/* Extracts the first element (or locks on the queue if no element is
 * available) 
 *
 * Returns 1 if thq_abort has been called on the queue, in which case the
 * element will not be extracted.
 */
int thq_extract (thrdqueue_t *thq, void **el);

/* Inserts an element (or locks on the queue if there are no slot
 * available).
 *
 * Returns 1 if thq_abort has been called on the queue, in which case the
 * element will NOT be inserted (therefore you may need to free it).
 */
int thq_insert (thrdqueue_t *thq, void *el);

/* Forces all waiting processes to return */
void thq_abort (thrdqueue_t *thq);

/* Extracts an element without locking if the queue is empty, and
 * returning 1 instead. Returns 0 the extraction succeeds (i.e. we have at
 * least one element).
 */
int thq_extract_nowait (thrdqueue_t *thq, void **el);

/* Deletes a queue. Note: you should call thq_abort() first in order to
 * avoid unpredicible behaviours. */
void thq_delete (thrdqueue_t *thq);

#endif // __defined_thrdqueue_h
