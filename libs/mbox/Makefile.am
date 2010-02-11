# Copyright (C) 2010 Giovanni [dacav] Simoni
#                    <simgidacav@gmail.com>
# 
# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation; either 
# version 3 of the License, or (at your option) any later 
# version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# 

AM_CFLAGS = -pthread -std=gnu99 -Wall -Werror -I./mbox/ \
            -I$(top_srcdir)/libs/thread_queue/ -D_GNU_SOURCE

lib_LIBRARIES = libmbox.a
include_HEADERS = mbox.h

includemboxdir = $(prefix)/include/mbox
includembox_HEADERS = mbox/descriptor.h mbox/error.h mbox/mail.h \
                      mbox/types.h

libmbox_a_SOURCES = $(include_HEADERS) \
                    $(includembox_HEADERS) \
                    control.c error.c interface.c mail.c split.c \
                    strings.c \
                    headers/datatypes.h headers/mail.h headers/parse.h \
                    headers/strings.h
