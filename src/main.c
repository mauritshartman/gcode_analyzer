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
    struct timeval start, stop;
    unsigned long long t;

    if((options = parse_options(argc, argv)) != NULL) {
        return EXIT_FAILURE;
    }

    // Try to load and parse the Gcode file:
    g = gcode_init();
    g->options = options;
    gettimeofday(&start, NULL);
    gcode_load(g);
    gettimeofday(&stop, NULL);

    t = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;
    printf("G-code file loaded (%ld bytes, %ld lines) in %.3f seconds (%.3f lines / second)\n",
        g->fileSize, g->filePos, ((double)t / 1000.0), ((double)g->filePos / ((double)t / 1000.0)));

    // Output and exit:
    show_output(g);
    return EXIT_SUCCESS;
}