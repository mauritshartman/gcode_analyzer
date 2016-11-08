#include "output.h"

#include <vector.h>
#include <jansson.h>

#include <stdio.h>


static void output_json(Gcode *g) {
    unsigned long long int t;
    json_t *output;
    char buf[32];
    ubyte i;
    print_area *pa;

    t = 1000 * (g->parse_stop->tv_sec - g->parse_start->tv_sec) + (g->parse_stop->tv_usec - g->parse_start->tv_usec) / 1000;
    printf("G-code file loaded (%ld Kbytes, %ld lines) in %.3f seconds (%.3f lines / second)\n",
        g->fileSize / 1000, g->filePos, ((double)t / 1000.0), ((double)g->filePos / ((double)t / 1000.0)));

    output = json_object();

    // Basic file information:
    json_object_set(output, "file_name", json_string(g->options->filename));
    json_object_set(output, "file_size", json_integer(g->fileSize));
    json_object_set(output, "number_of_lines", json_integer(g->filePos));

    // Relevant profile information:
    for (i = 0; i < g->options->offsets_set; i++) {
        sprintf(buf, "offset_extruder_%d", i);
        json_object_set(output, buf, json_vector3D(g->options->offsets[i]));
    }
    json_object_set(output, "feedrate", json_real(g->feedrate));
    json_object_set(output, "filament_diameter", json_real(g->filamentDiameter));
    json_object_set(output, "total_move_time_hours", json_real(g->totalMoveTimeMinute / 60.0));

    // Information about the gcode object:
    pa = gcode_printing_area(g);
    json_object_set(output, "minX", json_real(pa->minX));
    json_object_set(output, "minY", json_real(pa->minY));
    json_object_set(output, "minZ", json_real(pa->minZ));
    json_object_set(output, "maxX", json_real(pa->maxX));
    json_object_set(output, "maxY", json_real(pa->maxY));
    json_object_set(output, "maxZ", json_real(pa->maxZ));
    
    printf("%s\n", json_dumps(output, JSON_INDENT(1) | JSON_REAL_PRECISION(6)));
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

