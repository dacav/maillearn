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

AM_CFLAGS = -pthread -std=gnu99 -Wall -Werror -I./featsel/

lib_LIBRARIES = libfeatsel.a
include_HEADERS = featsel.h

includemboxdir = $(prefix)/include/featsel
includembox_HEADERS = featsel/feattuple.h featsel/types.h

libfeatsel_a_SOURCES = $(include_HEADERS) \
                       $(includembox_HEADERS) \
                       commander.c feattuple.c headers/datatypes.h
