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

#include "headers/datatypes.h"
#include "headers/strings.h"

#include <dacav.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
	dlist_free(mail->from, NULL);
	dlist_free(mail->to, NULL);
	dlist_free(mail->subject, NULL);
	dlist_free(mail->rows, free);

	free(mail);
}

void mail_set_from (mail_t *mail, const char *from)
{
	mail->from = dlist_append(mail->from, (void *)from);
}

void mail_set_to (mail_t *mail, const char *to)
{
	mail->to = dlist_append(mail->to, (void *)to);
}

void mail_set_subject (mail_t *mail, const char *subject)
{
	mail->subject = dlist_append(mail->subject, (void *)subject);
}

void mail_append (mail_t *mail, const char *row)
{
	mail->rows = dlist_append(mail->rows, (void *)row);
}

