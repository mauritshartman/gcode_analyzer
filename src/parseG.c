#include <parseG.h>
#include <vector.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


static bool inline parse_code_float(const char code, const char *line, float *f)
{
    char *s, c;
    if ((s = strchr(line, code)) != NULL) {     // Search line for given code character
        sscanf(s, "%c%f", &c, f);               // Char c should be same as code
        return true;
    }
    return false;
}


static void inline parse_G0_G1(Gcode *g, const char *line)
{
    float x = 0.0, y = 0.0, z = 0.0, e = 0.0, f = 0.0, moveTimeXYZ = 0.0, extrudeTime = 0.0;
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

    // Parse extruder:
    if (parse_code_float('E', line, &e)) {
        if (g->absoluteE) { e -= g->currentE[g->currentExtruder]; }     // make sure e is relative
        if (e > 0.0) { minmax3D_record(g->minMax, g->pos); }            // if move includes extrusion, calculate new min/max coordinates of model

        g->totalExtrusion[g->currentExtruder] += e;
        g->currentE[g->currentExtruder] += e;
        g->maxExtrusion[g->currentExtruder] = fmaxf(g->maxExtrusion[g->currentExtruder], g->totalExtrusion[g->currentExtruder]);
    }

    // Move time in x, y, z, will be 0 if no movement happened
    moveTimeXYZ = fabsf(vector3D_length(vector3D_sub(oldPos, g->pos)) / g->feedrate);
    // Time needed for extruding, will be 0 if no extrusion happened
    extrudeTime = fabsf(e / g->feedrate);
    // Time to add is maximum of both
    g->totalMoveTimeMinute += fmaxf(moveTimeXYZ, extrudeTime);

    //printf("Parsed G0/1: X=%.2f Y=%.2f Z=%.2f E=%.2f F=%.2f. Total move time (min): %.2f\n", x, y, z, e, f, g->totalMoveTimeMinute);
    free(oldPos);      // Is replaced with a newly allocated newPos
}


static void inline parse_G4(Gcode *g, const char *line)
{
    float s = 0.0, p = 0.0;
    if (parse_code_float('S', line, &s)) { g->totalMoveTimeMinute += (s / 60.0); }      // Seconds
    if (parse_code_float('P', line, &p)) { g->totalMoveTimeMinute += (s / 60000.0); }   // Milliseconds
}


static void inline parse_G28(Gcode *g, const char *line)
{
    float x = 0.0, y = 0.0, z = 0.0;
    bool x_found, y_found, z_found;             // Will be initialized in the next lines

    x_found = parse_code_float('X', line, &x);
    y_found = parse_code_float('Y', line, &y);
    z_found = parse_code_float('Z', line, &z);

    if (!x_found && !y_found && !z_found) {     // No homing coordinates given
        g->pos.x = 0.0;
        g->pos.y = 0.0;
        g->pos.z = 0.0;
    }
    else {  // Take the given homing coordinates:
        if (x_found) { g->pos.x = x; }
        if (y_found) { g->pos.y = y; }
        if (z_found) { g->pos.z = z; }
    }
}


void parse_G(Gcode *g, const int cmd, const char *line)
{
    switch(cmd) {
        case 0:     // Rapid linear move
        case 1:     // Linear move
            parse_G0_G1(g, line); break;
        case 4:     // Delay
            parse_G4(g, line); break;
        case 10:    // Retract
            g->totalMoveTimeMinute += g->fwretractTime; break;
        case 11:    // Unretract
            g->totalMoveTimeMinute += g->fwrecoverTime; break;
        case 20:    // Units in inches
            g->scale = 2.51; break;
        case 21:    // Units in mm
            g->scale = 1.0; break;
        case 28:    // Home
            parse_G28(g, line); break;
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