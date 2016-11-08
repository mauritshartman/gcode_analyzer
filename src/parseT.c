#include <parseT.h>


#include <stdio.h>

/* Tool selections / commands
 */
void parse_T(Gcode *g, const int tool_num, const char *line)
{
    ubyte tool = (ubyte)tool_num;      // Safety

    if (tool > 1) { fprintf(stderr, "GCODE tried to select tool %d, that looks wrong, ignoring for GCODE analysis", tool); }
    else {


        // Set new extruder:
        g->currentExtruder = tool;
    }
}