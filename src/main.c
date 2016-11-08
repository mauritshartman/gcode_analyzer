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
    gcode_options options;
    Gcode *g;
    struct timeval start, stop;
    unsigned long long t;

    parse_options(&options, argc, argv);

    // Try to load the Gcode file:
    gettimeofday(&start, NULL);
    
    g = gcode_init();
    gcode_load(g, options.filename);

    gettimeofday(&stop, NULL);
    t = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;
    printf("G-code file loaded (%ld bytes, %ld lines) in %.3f seconds (%.3f lines / second)\n",
        g->fileSize, g->filePos, ((double)t / 1000.0), ((double)g->filePos / ((double)t / 1000.0)));

    show_output(g, &options);

    return EXIT_SUCCESS;
}