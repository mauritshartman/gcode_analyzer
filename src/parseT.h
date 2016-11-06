/*
 * Parse gcode T-lines
 */

#ifndef PARSET_H
#define PARSET_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <gcode.h>


void parse_T(Gcode *g, const int, const char *line);


#ifdef  __cplusplus
}
#endif
 
#endif  /* PARSET_H */