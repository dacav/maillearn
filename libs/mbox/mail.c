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

#include "datatypes.h"
#include "stringhash.h"

#include <dacav.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define FIELDS_NBUCKETS 5

mail_t * mail_new ()
{
    mail_t *ret;

    assert(ret = malloc(sizeof(mail_t)));
    memset(ret, 0, sizeof(mail_t));

    //ret->fields = dhash_new(FIELDS_NBUCKETS, string_hash, strcmp);

    return ret;
}

void mail_free (mail_t *mail)
{
    //dhash_free(ret->fields, free, free);

    /* Note: this works even if the fields are NULL */
    free((void *)(mail->from));
    free((void *)(mail->to));
    free((void *)(mail->subject));
}

