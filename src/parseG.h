/*
 * Parse gcode G-lines
 */

#ifndef PARSEG_H
#define PARSEG_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <gcode.h>


void parse_G(Gcode *g, char *line);


#ifdef  __cplusplus
}
#endif
 
#endif  /* PARSEG_H */