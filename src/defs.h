/*
 * General definitions
 */

#ifndef DEFS_H
#define DEFS_H
 
#ifdef  __cplusplus
extern "C" {
#endif


#include <stdbool.h>

#define GCODE_VERSION "Gcode_analyzer 0.0.1"


/* General types */
typedef unsigned char       ubyte;  // [0 - 255]
typedef signed char         sbyte;  // [-128 - 127]
typedef short               sint16; // [-32768 - 32767]
typedef unsigned short      uint16; // [0 - 65536]
typedef long                sint32; // [-2147483648 - 2147483647]
typedef unsigned long       uint32; // [0 - 4294967295]


/* GCODE definitions */


#ifdef  __cplusplus
}
#endif
 
#endif  /* DEFS_H */