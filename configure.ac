# Copyright (C) 2009 2010 Giovanni [dacav] Simoni
# 						  <simgidacav@gmail.com>
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

AC_PREREQ([2.65])
AC_INIT([maillearn], [0.1], [simgidacav@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([src/config.h])

AM_INIT_AUTOMAKE([-Wall])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

AC_CONFIG_MACRO_DIR([m4])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

AC_CHECK_HEADER([dacav.h],[],
                [AC_MSG_ERROR(libdacav not found.  Please install libdacav)])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap])

AC_CONFIG_FILES([Makefile
                 libs/mbox/Makefile
                 libs/thread_queue/Makefile
                 libs/featsel/Makefile
                 libs/featsel/tests/Makefile
                 src/Makefile])

AC_OUTPUT
