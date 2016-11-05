/*
 * Output processor
 */

#ifndef OUTPUT_H
#define OUTPUT_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <gcode.h>
#include <arguments.h>


void show_output(Gcode *, gcode_options *);


#ifdef  __cplusplus
}
#endif
 
#endif  /* OUTPUT_H */