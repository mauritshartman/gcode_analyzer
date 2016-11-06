/*
 * Vector3D object
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <defs.h>

/* Specific GCODE analyze types and functions */
typedef struct {
    float x;
    float y;
    float z;

    bool x_none;
    bool y_none;
    bool z_none;
} Vector3D;


Vector3D *vector3D_init(float x, float y, float z);
Vector3D *vector3D_init2(void);
Vector3D *vector3D_copy(Vector3D *);
Vector3D *vector3D_add(Vector3D *, Vector3D *);
Vector3D *vector3D_sub(Vector3D *, Vector3D *);
Vector3D *vector3D_mul(Vector3D *, float);
Vector3D *vector3D_abs(Vector3D *);
bool vector3D_eq(Vector3D *, Vector3D *);
float vector3D_length(Vector3D *);
char *vector3D_str(Vector3D *, char *, uint16);



/* GCODE definitions */


#ifdef  __cplusplus
}
#endif
 
#endif  /* VECTOR3D_H */