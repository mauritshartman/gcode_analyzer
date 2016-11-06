# Build the jansson JSON library first:
SUBDIRS = jansson

# Flags to pass to C compiler, pre-processor and linker:
AM_CFLAGS = --pedantic -Wall -std=c99 -O0 -pg
AM_CPPFLAGS = -I$(srcdir)/jansson/src
AM_LDFLAGS = -lm

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
sbin_PROGRAMS = gcode_analyze
noinst_LTLIBRARIES = libgcode_analyze.la

libgcode_analyze_la_SOURCES =   defs.h \
                                arguments.c arguments.h \
                                vector.c vector.h \
                                list.c list.h \
                                dict.c dict.h \
                                gcode.c gcode.h \
                                minmax.c minmax.h \
                                output.c output.h \
                                parseG.c parseG.h \
                                parseM.c parseM.h \
                                parseT.c parseT.h \
                                util.c util.h
libgcode_analyze_la_LIBADD =    jansson/src/libjansson.la


gcode_analyze_SOURCES =         main.c
# Link with the libtool convenience library:
gcode_analyze_LDADD =           libgcode_analyze.la