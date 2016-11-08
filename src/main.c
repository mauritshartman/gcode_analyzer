#include <defs.h>
#include <vector.h>
#include <gcode.h>
#include <arguments.h>
#include <output.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


int main(int argc, char* argv[])
{
    gcode_options *options;
    Gcode *g;

    if((options = parse_options(argc, argv)) == NULL) {
        return EXIT_FAILURE;
    }

    // Try to load and parse the Gcode file:
    g = gcode_init();
    g->options = options;
    gcode_load(g);

    // Output and exit:
    show_output(g);
    gcode_free(g);
    return EXIT_SUCCESS;
}