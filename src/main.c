#include <defs.h>
#include <vector.h>
#include <gcode.h>
#include <arguments.h>

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    char buf[512];
    gcode_options options;

    parse_options(&options, argc, argv);

    Vector3D *v = vector3D_init(1, 2, 3);
    printf("The vector is %s\n", vector3D_str(v, buf, sizeof(buf)));

    Gcode *g = gcode_init();
    gcode_load(g, options.filename);

    printf("Loaded file and its size is %ld bytes, %ld lines\n", g->fileSize, g->filePos);


    return EXIT_SUCCESS;
}