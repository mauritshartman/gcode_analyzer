#include "minmax.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>


/* Allocate a new MinMax3D object */
MinMax3D *minmax3D_init(void)
{
    MinMax3D *m = malloc(sizeof(MinMax3D));
    memset(m, '\0', sizeof(MinMax3D));

    m->min = vector3D_init(0.0, 0.0, 0.0);  // TODO: check?
    m->max = vector3D_init(0.0, 0.0, 0.0);

    return m;
}


/* Return a vector with the total size (volume) of the MinMax3D object: */
Vector3D *minmax3D_size(MinMax3D *m)
{
    Vector3D *v = vector3D_init2();     /* TODO memory leak */

    v->x = fabsf(m->max->x - m->min->x);
    v->y = fabsf(m->max->y - m->min->y);
    v->z = fabsf(m->max->z - m->min->z);
    
    return v;
}


/* Record a new coordinate and update minmax. Return updated minmax */
MinMax3D *minmax3D_record(MinMax3D *m, Vector3D *coord)
{
    Vector3D *curr_min, *curr_max;
    curr_min = m->min;
    curr_max = m->max;

    /* X coordinates */
    if (curr_min->x_none || coord->x < curr_min->x) {
        curr_min->x = coord->x;
        curr_min->x_none = false;
    }
    else if (curr_max->x_none || coord->x > curr_max->x) {
        curr_max->x = coord->x;
        curr_max->x_none = false;
    }

    /* Y coordinates */
    if (curr_min->y_none || coord->y < curr_min->y) {
        curr_min->y = coord->y;
        curr_min->y_none = false;
    }
    else if (curr_max->y_none || coord->y > curr_max->y) {
        curr_max->y = coord->y;
        curr_max->y_none = false;
    }

    /* Z coordinates */
    if (curr_min->z_none || coord->z < curr_min->z) {
        curr_min->z = coord->z;
        curr_min->z_none = false;
    }
    else if (curr_max->z_none || coord->z > curr_max->z) {
        curr_max->z = coord->z;
        curr_max->z_none = false;
    }

    return m;
}