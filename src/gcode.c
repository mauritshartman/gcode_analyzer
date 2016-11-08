#include <gcode.h>
#include <util.h>
#include <parseG.h>
#include <parseM.h>
#include <parseT.h>

#include <stdlib.h>
#include <string.h>


/* Initialize and create a new Gcode object */
Gcode *gcode_init(void)
{
    Gcode *g = malloc(sizeof(Gcode));
    memset(g, '\0', sizeof(Gcode));

    g->minMax = minmax3D_init();
    g->abort = false;
    g->pos = vector3D_init(0.0, 0.0, 0.0);
    g->posOffset = vector3D_init(0.0, 0.0, 0.0);
    g->absoluteE = true;
    g->scale = 1.0;
    g->posAbs = true;
    g->filamentDiameter = 0.0;
    g->currentExtruder = 0;

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
static void open_file_and_determine_size(Gcode *g)
{
    // Try to open the gcode file read-only:
    if ((g->file = fopen(g->options->filename, "r")) == NULL) {
        fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__);
        exit(EXIT_FAILURE);
    }

    // Determine file size:
    fseek(g->file, 0L, SEEK_END);
    g->fileSize = ftell(g->file);
    rewind(g->file);
}


// Parse gcode comments (;) from a given line of gcode
static void inline parse_gcode_comment(Gcode *g, const char *line)
{
    char *comment;
    char *fil_token, *tok;
    char buf[128];

    comment = strchr(line, ';') + 1;    // Should be safe (null-terminated string and ; known to be present)
    strip(buf, sizeof(buf), comment);
    if ((fil_token = strstr(buf, "filament_diameter")) != NULL) {
        tok = strtok(fil_token, "=");       // Should be filament_diameter
        tok = strtok(fil_token, "=");       // Second token, after the '=' sign
        if (tok) {
            g->filamentDiameter = atof(tok);         // Convert to float - will also discard whitespace. If no conversion is possible, it sets 0.0
        } 
    }

    // TODO CURA profiles not parsed now
}


// Parse a single line of gcode:
static void inline parse_line(Gcode *g, char *line)
{
    char cmd_letter;
    int cmd_number, scanned;

    g->filePos++;
    g->readBytes += strlen(line);

    if ((scanned = sscanf(line, "%c%d", &cmd_letter, &cmd_number)) != EOF) {
        switch (cmd_letter) {
            case 'G':
                parse_G(g, cmd_number, line);
                break;
            case 'M':
                parse_M(g, cmd_number, line);
                break;
            case 'T':
                if (scanned == 2) { parse_T(g, cmd_number, line); }     // There should be a tool number
                break;
                /* Unclear whether comment lines need to start with a semicolon, or if whitespace is allowed first. If not, then the following is more efficient: */
            case ';':
                parse_gcode_comment(g, line);
                break;
            default:    // Silently ignore other gcode lines
                break;
        }
    }
}


void gcode_load(Gcode *g)
{
    char line[128];
    memset (line, '\0', sizeof(line));  // Probably not necessary as fgets overwrites this, including '\0'

    open_file_and_determine_size(g);
    
    // Parse all the lines in the gcode file:
    while (fgets(line, sizeof(line), g->file) != NULL) {
        parse_line(g, line);
    }

    fclose(g->file);
}