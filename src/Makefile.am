# Build the jansson JSON library first:
SUBDIRS = jansson

# Flags to pass to C compiler, pre-processor and linker:
AM_CFLAGS = --pedantic -Wall -std=c99 -O2
AM_CPPFLAGS = -I$(srcdir)/jansson
AM_LDFLAGS = -lm

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
sbin_PROGRAMS = gcode_analyze

gcode_analyze_SOURCES =     main.c \
                            defs.h \
                            arguments.c arguments.h \
                            vector.c vector.h \
                            list.c list.h \
                            dict.c dict.h \
                            gcode.c gcode.h \
                            minmax.c minmax.h \
                            output.c output.h \
                            util.c util.h
# Link with the jansson JSON library built in the subdir:
gcode_analyze_LDADD = jansson/src/libjansson.la