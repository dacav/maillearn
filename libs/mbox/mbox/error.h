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

#ifndef __defined_mbox_error_h
#define __defined_mbox_error_h

#include <stdio.h>

typedef enum {
    MBOX_SUCCESS = 0,
    MBOX_OPENING
} mbox_err_t;

/** Convert a mbox_err_t value into the corresponding string
 *
 * @param err The error code;
 * @return The corresponding error string.
 */
const char * mbox_strerr (mbox_err_t err);

#endif // __defined_mbox_error_h
