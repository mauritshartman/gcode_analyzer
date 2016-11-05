#include <defs.h>
#include <vector.h>
#include <gcode.h>
#include <arguments.h>
#include <output.h>

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    gcode_options options;
    Gcode *g;

    parse_options(&options, argc, argv);

    // Try to load the Gcode file:
    g = gcode_init();
    gcode_load(g, options.filename);
    printf("File loaded and its size is %ld bytes, %ld lines\n", g->fileSize, g->filePos);

    show_output(g, &options);

    return EXIT_SUCCESS;
}