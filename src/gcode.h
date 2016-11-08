/*
 * GCODE object
 */

#ifndef GCODE_H
#define GCODE_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <vector.h>
#include <minmax.h>
#include <arguments.h>

#include <stdio.h>

/* Specific GCODE analyze types and functions */
typedef struct {
	float extrusionAmount[2];	// For left and right extruder
	float extrusionVolume[2];
	float totalMoveTimeMinute;
	FILE *file;
	uint32 fileSize;
	bool abort;
	float filamentDiameter;
	MinMax3D *minMax;

	uint32 filePos;
	uint32 readBytes;
	Vector3D *pos;
	Vector3D *posOffset;

	float currentE[2];
	float totalExtrusion[2];
	float maxExtrusion[2];
	ubyte currentExtruder;
	
	bool absoluteE;
	float scale;
	bool posAbs;

	float fwretractTime;
	float fwretractDist;
	float fwrecoverTime;

	float feedrate;
	
	gcode_options *options;
} Gcode;

typedef struct {
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
} print_area;


Gcode *gcode_init(void);
Vector3D *gcode_dimensions(Gcode *);
print_area *gcode_printing_area(Gcode *);
void gcode_load(Gcode *); 		// Add profile


#ifdef  __cplusplus
}
#endif
 
#endif  /* GCODE_H */