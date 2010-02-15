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

#ifndef __defined_mbox_mail_h
#define __defined_mbox_mail_h

#include <dacav.h>

/** Frees a mail object 
 *
 * param mail The mail to be freed.
 */
void mbox_mail_free (mbox_mail_t *mail);

/** Getter for attribute.
 *
 * @param mail The mail whose attribute will be extracted;
 * @param key The attribute name;
 * @return The required attribute (or NULL if such an attribus does not
 *         exist in the mail attribute set).
 */
const char *mbox_mail_getattr (mbox_mail_t *mail, const char *key);

/* Getter for tracing information.
 *  
 * Tracing information is a list of Received and Return-path fields.
 *
 * @note The return value is deallocated automatically when
 *       mbox_mail_free is called.
 *
 * @param @mail The mail whose trace will be extracted;
 * @return A list of trace elements.
 */
const dlist_t *mbox_mail_gettrace (mbox_mail_t *mail);

/** Returns the body of the mail as constant string
 *
 * @note The return value is deallocated automatically when
 *       mbox_mail_free is called.
 *
 * @param mail The mail whose body will be extracted;
 * @return A long, null-terminated string with \n characters.
 */
const char *mbox_mail_getbody (mbox_mail_t *mail);

#endif // __defined_mbox_mail_h
