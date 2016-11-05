#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([gcode_analyze], [0.0.1], [m.hartman@lpfrg.com])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/defs.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

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
AC_CHECK_FUNCS([    memset sqrt fabsf fseek ftell fgets strlen getopt_long puts printf strchr strstr])

AC_CONFIG_FILES([
            config.h
            Makefile
            src/Makefile
            test/Makefile
])
AC_OUTPUT
