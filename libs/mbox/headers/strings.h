/*
 * Copyright 2009 2010 Giovanni Simoni
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

#ifndef __defined_stringhash_h
#define __defined_stringhash_h

#include <stdlib.h>

/* A hashing function for string, suitable for libdacav hashtables. */
unsigned long string_hash (const unsigned char *name);

/* Automatic allocation of a new string. For freeing just use free.
 * The len parameter is not comprensive of the trailing zero, so len+1
 * bytes will be allocated, and 0 will be inserted at the end of the
 * string.
 */
char *string_alloc (char *orig, size_t len);

#endif // __defined_stringhash_h

