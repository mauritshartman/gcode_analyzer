#include "output.h"

#include <jansson.h>

#include <stdio.h>


static void output_json(Gcode *g) {
    unsigned long long int t;
    json_t *output;

    t = 1000 * (g->parse_stop->tv_sec - g->parse_start->tv_sec) + (g->parse_stop->tv_usec - g->parse_start->tv_usec) / 1000;
    printf("G-code file loaded (%ld Kbytes, %ld lines) in %.3f seconds (%.3f lines / second)\n",
        g->fileSize / 1000, g->filePos, ((double)t / 1000.0), ((double)g->filePos / ((double)t / 1000.0)));

    output = json_object();

    // Basic file information:
    json_object_set(output, "file_name", json_string(g->options->filename));
    json_object_set(output, "file_size", json_integer(g->fileSize));
    json_object_set(output, "number_of_lines", json_integer(g->filePos));
    json_object_set(output, "number_of_lines", json_integer(g->filePos));


    // Information about the gcode object:
    
    printf("%s\n", json_dumps(output, JSON_INDENT(3)));
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

