#include "output.h"

#include <stdio.h>


static void output_json(Gcode *g) {
    puts("{");


    puts("}");
}


static void output_xml(Gcode *g) {
    puts("Not implemented");
}


void show_output(Gcode *g, gcode_options *options)
{
    if (options->output == JSON) {
        output_json(g);
    }
    else if (options->output == XML) {
        output_xml(g);
    }
}

