/*
 * MinMax3D object
 */

#ifndef MINMAX3D_H
#define MINMAX3D_H
 
#ifdef  __cplusplus
extern "C" {
#endif

#include <vector.h>

/* Specific GCODE analyze types and functions */
typedef struct {
    Vector3D *min;
    Vector3D *max;
} MinMax3D;

MinMax3D *minmax3D_init(void);
Vector3D *minmax3D_size(MinMax3D *);
MinMax3D *minmax3D_record(MinMax3D *, Vector3D *);



#ifdef  __cplusplus
}
#endif
 
#endif  /* MINMAX3D_H */