/*
 * Parse gcode M-lines
 */

#ifndef PARSEM_H
#define PARSEM_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <gcode.h>


void parse_M(Gcode *g, char *line);


#ifdef  __cplusplus
}
#endif
 
#endif  /* PARSEM_H */