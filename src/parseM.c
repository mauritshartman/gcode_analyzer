#include <parseM.h>


#include <string.h>
#include <stdio.h>


// TODO double code with parseG.c
static bool inline parse_code_float2(const char code, const char *line, float *f)
{
    char *s, c;
    if ((s = strchr(line, code)) != NULL) {     // Search line for given code character
        sscanf(s, "%c%f", &c, f);               // Char c should be same as code
        return true;
    }
    return false;
}


static void inline parse_M207_M208(Gcode *g, const int cmd, const char *line)
{
    float s = 0.0, f = 0.0;
    if (parse_code_float2('S', line, &s) && parse_code_float2('F', line, &f)) {
        if (cmd == 207) {
            g->fwretractTime = s / f;
            g->fwretractDist = s;
        }
        else {
            g->fwrecoverTime = (g->fwretractDist + s) / f;
        }
    }
}


void parse_M(Gcode *g, const int cmd, const char *line)
{
    switch(cmd) {
        case 82:        // Absolute E
            g->absoluteE = true; break;
        case 83:        // Relative E
            g->absoluteE = false; break;    
        case 207:       // Firmware retract settings
        case 208:
            parse_M207_M208(g, cmd, line); break;  
        default:
            // Silently ignore other gcode G-commands:
            break;
    }
}