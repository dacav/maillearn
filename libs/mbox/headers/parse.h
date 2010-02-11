/*
 * Copyright 2010 Giovanni Simoni
 *
 * This file is part of parselearn.
 *
 * parselearn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * parselearn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with parselearn.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __defined_parse_h
#define __defined_parse_h

#include <mbox.h>

void parse_init (parse_t *p);
void parse_free (parse_t *p);

/* Returns 1 if the match succeded and 0 otherwise */
int  parse_match (parse_t *parse, char *str, char **key, char **value);

#endif // __defined_parse_h
