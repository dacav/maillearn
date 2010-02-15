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

#ifndef __defined_featsel_types_h
#define __defined_featsel_types_h

/** Feature selection callback.
 *
 * This kind of function is called for an element to be analyzed.
 *
 * @param elem The element to analyze;
 * @param data Private user data;
 * @return The feature valutation.
 */
typedef double (*feat_fun_t) (void *elem, void *udata);

typedef struct feat_tuple feat_tuple_t;

typedef struct featsel featsel_t;

#endif // __defined_featsel_types_h
