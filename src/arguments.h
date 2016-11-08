/*
 * Command line arguments
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <defs.h>
#include <vector.h>

#include <jansson.h>

typedef enum {JSON, XML} output_options_type;

typedef struct {
    char *filename;
    output_options_type output;
    json_t *profile;

    float feedrate;
    Vector3D *offsets[2];       // TODO: max 2 extruders?
    ubyte offsets_set;          // Number of offsets parsed from profile
} gcode_options;


/* Try to parse command line options and return in a gcode_options struct. If unable, return NULL */
gcode_options *parse_options(int argc, char *argv[]);


#ifdef  __cplusplus
}
#endif
 
#endif  /* ARGUMENTS_H */