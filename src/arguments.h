/*
 * Command line arguments
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <defs.h>

typedef struct {
    char *filename;
} gcode_options;


void parse_options(gcode_options *, int argc, char *argv[]);


#ifdef  __cplusplus
}
#endif
 
#endif  /* ARGUMENTS_H */