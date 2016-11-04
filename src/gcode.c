#include <gcode.h>

#include <stdlib.h>
#include <string.h>


/* Initialize and create a new Gcode object */
Gcode *gcode_init(void)
{
    Gcode *g = malloc(sizeof(Gcode));
    memset(g, '\0', sizeof(Gcode));

    g->minMax = minmax3D_init();
    g->abort = false;
    g->pos = vector3D_init(0, 0, 0);
    g->posOffset = vector3D_init(0, 0, 0);
    g->absoluteE = true;
    g->scale = 1.0;
    g->posAbs = true;

    g->feedrate = 2000; /* feedrate = min(printer_profile["axes"]["x"]["speed"], printer_profile["axes"]["y"]["speed"]) */

    return g;
}


// Return a vector with the dimensions of the gocde
Vector3D *gcode_dimensions(Gcode *g)
{
    return minmax3D_size(g->minMax);
}


// Return a print_area object with the volume:
print_area *gcode_printing_area(Gcode *g)
{
    print_area *ret = malloc(sizeof(print_area));
    memset(ret ,'\0', sizeof(print_area));

    ret->minX = g->minMax->min->x;
    ret->minY = g->minMax->min->y;
    ret->minZ = g->minMax->min->z;
    ret->maxX = g->minMax->max->x;
    ret->maxY = g->minMax->max->y;
    ret->maxZ = g->minMax->max->z;

    return ret;
}


// Open the named file and set the file descriptor. Then determine file size.
static void open_file_and_determine_size(Gcode *g, char *filename)
{
    // Open the gcode file read-only:
    g->file = fopen(filename, "r");
    if (g->file == NULL) {
        fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__);
        exit(EXIT_FAILURE);
    }
    // Determine file size:
    fseek(g->file, 0L, SEEK_END);
    g->fileSize = ftell(g->file);
    rewind(g->file);
}


// Parse a single line of gcode:
static void parse_line(Gcode *g, char *buf)
{
    g->filePos++;
    g->readBytes += strlen(buf);
}


void gcode_load(Gcode *g, char *filename)
{
    char buf[128];

    open_file_and_determine_size(g, filename);
    
    // Parse all the lines in the gcode file:
    while (fgets(buf, sizeof(buf), g->file) != NULL) {
        parse_line(g, buf);
    }
}