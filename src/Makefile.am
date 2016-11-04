# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -O2 -mfloat-abi=hard
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
                            minmax.c minmax.h