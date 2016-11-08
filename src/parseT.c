#include <parseT.h>


#include <stdio.h>

/* Tool selections / commands
 */
void parse_T(Gcode *g, const int tool_num, const char *line)
{
    ubyte tool = (ubyte)tool_num;      // Safety

    if (tool > 1) { fprintf(stderr, "GCODE tried to select tool %d, that looks wrong, ignoring for GCODE analysis", tool); }
    else {      // Tool either 0 or 1
        // Undo application of tool offsets for old extruder:
        if ((tool + 1) <= g->options->offsets_set) {     // Only apply offsets if they are in the profile
            g->posOffset->x -= g->options->offsets[g->currentExtruder]->x;
            g->posOffset->y -= g->options->offsets[g->currentExtruder]->y;
        }

        // Set new extruder:
        g->currentExtruder = tool;

        // Apply tool offsets for newly selected extruder:
        if ((tool + 1) <= g->options->offsets_set) {     // Only apply offsets if they are in the profile
            g->posOffset->x += g->options->offsets[g->currentExtruder]->x;
            g->posOffset->y += g->options->offsets[g->currentExtruder]->y;
        }

        /* TODO Python code not fully understood:
        if len(currentE) <= currentExtruder:
            for i in range(len(currentE), currentExtruder + 1):
                currentE.append(0.0)
        if len(maxExtrusion) <= currentExtruder:
            for i in range(len(maxExtrusion), currentExtruder + 1):
                maxExtrusion.append(0.0)
        if len(totalExtrusion) <= currentExtruder:
            for i in range(len(totalExtrusion), currentExtruder + 1):
                totalExtrusion.append(0.0)
        */
    }
}