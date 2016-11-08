#include "output.h"

#include <stdio.h>


static void output_json(Gcode *g) {
    unsigned long long int t;

    t = 1000 * (g->parse_stop->tv_sec - g->parse_start->tv_sec) + (g->parse_stop->tv_usec - g->parse_start->tv_usec) / 1000;
    printf("G-code file loaded (%ld Kbytes, %ld lines) in %.3f seconds (%.3f lines / second)\n",
        g->fileSize / 1000, g->filePos, ((double)t / 1000.0), ((double)g->filePos / ((double)t / 1000.0)));
}


static void output_xml(Gcode *g) {
    puts("Not implemented");
}


void show_output(Gcode *g)
{
    if (g->options->output == JSON) {
        output_json(g);
    }
    else if (g->options->output == XML) {
        output_xml(g);
    }
}

