#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([gcode_analyze], [0.0.2], [m.hartman@lpfrg.com])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/defs.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

AC_PROG_LIBTOOL
LT_CONFIG_LTDL_DIR([libltdl])
LTDL_INIT
AC_CONFIG_MACRO_DIRS([libltdl/m4])


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h stddef.h ctypes.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T
AC_TYPE_LONG_LONG_INT


# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([    memset sqrtf fabsf fseek ftell fgets strlen getopt_long puts printf strchr strstr fminf])

AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_CONFIG_SUBDIRS([src/jansson])
AC_OUTPUT
