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

#include <mbox.h>

#include "datatypes.h"
#include "strings.h"
#include "parse.h"

#include <regex.h>

#define PARSE_BUFLEN    32
#define PARSE_FMT       "%32s"

static inline
int match_mailstart (parse_t *p, const char *str)
{
    return regexec(&p->mailstart, str, 0, NULL, 0) == 0
}

void mbox_parse (mbox_t *mbox)
{
    char buffer[PARSE_BUFLEN];
    parse_t *p = &mbox->parse;
    int val;

    while ((val = fscanf(mbox->file, PARSE_FMT, buffer) != EOF)
            && val > 0) {
        if (match_mailstart(p, buffer)) {
            printf("FOUND? '%s'\n", buffer);
        }
    }
}

void parse_init (parse_t *p)
{
    assert(!regcomp(&p->mailstart, "^From: .*$", REG_NOSUB));
}

void parse_free (parse_t *p)
{
    regfree(&p->mailstart);
}


