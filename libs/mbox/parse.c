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

#include <mbox.h>

#include <assert.h>
#include <dacav.h>
#include <string.h>

#include "headers/datatypes.h"
#include "headers/parse.h"
#include "headers/strings.h"

#define PARSE_HASH_SIZE 20

void parse_init (parse_t *p)
{
    assert(regcomp(&p->field, "^([^: ]+) *: *(.+)$", REG_EXTENDED) == 0);
    p->keys = dhash_new(PARSE_HASH_SIZE, (dhash_func_t)string_hash,
                        (dcmp_func_t)strcmp);
    p->accumulator = dlist_new();
}

void parse_free (parse_t *p)
{
    regfree(&p->field);
    dhash_free(p->keys, free, NULL);
    dlist_free(p->accumulator, free);
}

int  parse_match (parse_t *parse, char *str, char **key, char **value)
{
    register char *tmp;
    regmatch_t match[3];
    char remember;

    if (regexec(&parse->field, str, 3, match, 0) == REG_NOMATCH) {
        return 0;
    }

    /* Temporarily replace the end bound of the first match (this allows
     * us to get a null-terminated string) */
    tmp = str + match[1].rm_eo;
    remember = *tmp; *tmp = 0;
    if (dhash_search(parse->keys, (const void *)str, (void **)key) ==
            DHASH_NOTFOUND) {
        /* Since we didn't find the key, we allocate it bare new */
        register char *s;

        s = string_alloc(str, match[1].rm_eo);
        *key = s;
        dhash_insert(parse->keys, (const void *)s, (const void *)s);
    }
    *tmp = remember;

    /* Same trick for value. This time allocate it without asking. */
    tmp = str + match[2].rm_eo;
    remember = *tmp; *tmp = 0;
    *value = string_alloc(str + match[2].rm_so,
                          match[2].rm_eo - match[2].rm_so);
    *tmp = remember;

    return 1;
}

