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
#include "strings.h"

#include <dacav.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define FIELDS_NBUCKETS 5

mail_t * mail_new ()
{
    mail_t *ret;

    assert(ret = malloc(sizeof(mail_t)));

	ret->from = dlist_new();
	ret->to = dlist_new();
	ret->subject = dlist_new();

	ret->rows = dlist_new();

    return ret;
}

void mail_free (mail_t *mail)
{
	dlist_free(mail->from, free);
	dlist_free(mail->to, free);
	dlist_free(mail->subject, free);
	dlist_free(mail->rows, free);

	free(mail);
}

#include <stdio.h>
void mail_set_from (mail_t *mail, const char *from)
{
	printf("Setting from: '%s'\n", from);
	mail->from = dlist_append(mail->from, (void *)from);
}

void mail_set_to (mail_t *mail, const char *to)
{
	printf("Setting to: '%s'\n", to);
	mail->to = dlist_append(mail->to, (void *)to);
}

void mail_set_subject (mail_t *mail, const char *subject)
{
	printf("Setting subject: '%s'\n", subject);
	mail->subject = dlist_append(mail->subject, (void *)subject);
}

void mail_append (mail_t *mail, const char *row)
{
	printf("Generic line: '%s'\n", row);
	mail->rows = dlist_append(mail->rows, (void *)row);
}

