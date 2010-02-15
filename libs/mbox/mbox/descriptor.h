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

#ifndef __defined_mbox_descriptor_h
#define __defined_mbox_descriptor_h

/** Initialize a threaded mailbox reader.
 *
 * @param filename The mbox file to be read;
 * @param mbox The location where the new instance will be stored;
 * @return MBOX_SUCCESS on success, an error code otherwise.
 */
mbox_err_t mbox_new (const char *filename, mbox_t **mbox);

/** Free a mbox.
 *
 * Since an mbox_t object is threaded, this call will block the calling
 * thread until the reading phase is completed.
 *
 * @param mbox The mbox_t object to free.
 */
void mbox_free (mbox_t *mbox);

/** Extracts a mail.
 *
 * If there are no mail available yet, this call will block the calling
 * thread until a new mail will be available. If there are no more mail to
 * read this call will simply return NULL.
 *
 * @param mbox The mbox_t object where to extract the mail;
 * @return The mail object.
 */
mbox_mail_t *mbox_next_mail (mbox_t *mbox);

#endif // __defined_mbox_descriptor_h
