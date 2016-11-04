# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -O2

AM_LDFLAGS =            -L$(top_srcdir)/src

AM_CPPFLAGS =           -I$(top_srcdir)/src

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
noinst_PROGRAMS =       test_list

test_list_SOURCES =     test_list.c