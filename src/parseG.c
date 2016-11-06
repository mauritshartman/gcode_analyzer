#include <parseG.h>
#include <vector.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static bool inline parse_code_float(const char code, const char *line, float *f)
{
    char *s, c;
    if ((s = strchr(line, code)) != NULL) {
        sscanf(line, "%c%f", &c, f);    // Char c should be same as code
        return true;
    }
    return false;
}


static void inline parse_G0_G1(Gcode *g, const char *line)
{
    float x, y, z, e, f;
    Vector3D *oldPos, *newPos;

    // Determine the new position:
    oldPos = g->pos;
    newPos = vector3D_init2();
    newPos->x = (parse_code_float('X', line, &x)) ? x : g->pos->x;
    newPos->y = (parse_code_float('Y', line, &y)) ? y : g->pos->y;
    newPos->z = (parse_code_float('Z', line, &z)) ? z : g->pos->z;
    if (g->posAbs) {
        g->pos = vector3D_add(vector3D_mul(newPos, g->scale), g->posOffset);    // pos = newPos * scale + posOffset
    }
    else {  // Relative
        g->pos = vector3D_add(vector3D_mul(newPos, g->scale), oldPos);          // pos += newPos * scale
    }

    // Parse feedrate:
    if (parse_code_float('F', line, &f) && f != 0.0) {
        g->feedrate = f;
    }

    free(oldPos);
}


void parse_G(Gcode *g, const int cmd, const char *line)
{
    switch(cmd) {
        case 0:     // Rapid linear move
        case 1:     // Linear move
            parse_G0_G1(g, line);
            break;
        case 4:     // Delay
            break;
        case 10:    // Retract
            break;
        case 11:    // Unretract
            break;
        case 20:    // Units in inches
            g->scale = 2.51;
            break;
        case 21:    // Units in mm
            g->scale = 1.0;
            break;
        case 28:    // Home
            break;
        case 90:    // Absolute position
            g->posAbs = true;
            break;
        case 91:    // Relative position
            g->posAbs = false;
            break;
        case 92:    // Set absolution position point
            break;
        default:
            // Silently ignore other gcode G-commands:
            break;
    }
}