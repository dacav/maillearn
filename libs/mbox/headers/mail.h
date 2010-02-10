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

#ifndef __defined_mail_h
#define __defined_mail_h

mail_t * mail_new ();

void mail_set_from (mail_t *mail, const char *from);
void mail_set_to (mail_t *mail, const char *to);
void mail_set_subject (mail_t *mail, const char *subject);
void mail_append (mail_t *mail, const char *row);

#endif // __defined_mail_h
