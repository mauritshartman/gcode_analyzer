/*
 *
 */

#include "vector.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Malloc a Vector3D and initialize with values */
Vector3D *vector3D_init(float x, float y, float z)
{
    Vector3D *v = malloc(sizeof(Vector3D));
    memset(v, '\0', sizeof(Vector3D));

    v->x = x;
    v->y = y;
    v->z = z;

    v->x_none = false;
    v->y_none = false;
    v->z_none = false;

    return v;
}


/* Malloc an empty Vector3D */
Vector3D *vector3D_init2(void)
{
    Vector3D *v = malloc(sizeof(Vector3D));
    memset(v, '\0', sizeof(Vector3D));

    v->x_none = true;
    v->y_none = true;
    v->z_none = true;

    return v;
}


Vector3D *vector3D_copy(Vector3D *old)
{
    Vector3D *v = vector3D_init(old->x, old->y, old->z);
    v->x_none = old->x_none;
    v->y_none = old->y_none;
    v->z_none = old->z_none;
    
    return v;
}


/* Add two vector and place the result in the first vector. Return the pointer to the first vector: */
Vector3D *vector3D_add(Vector3D *a, Vector3D *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
    return a;
}


/* Subtract vector b from vector a and return the pointer to a: */
Vector3D *vector3D_sub(Vector3D *a, Vector3D *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
    return a;
}


/* Multiply vectors a and b, and return pointer to a: */
Vector3D *vector3D_mul(Vector3D *a, Vector3D *b)
{
    a->x *= b->x;
    a->y *= b->y;
    a->z *= b->z;
    return a;
}


/* Change the given vector and make all values absolute: */
Vector3D *vector3D_abs(Vector3D *a)
{
    a->x = (a->x < 0) ? -a->x : a->x;
    a->y = (a->y < 0) ? -a->y : a->y;
    a->z = (a->z < 0) ? -a->z : a->z;
    return a;
}


/* True iff vectors a and b are equal: */
bool vector3D_eq(Vector3D *a, Vector3D *b)
{
    return (a->x == b->x && a->y == b->y && a->z == b->z);
}


/* Return the length of the given vector: */
float vector3D_length(Vector3D *a)
{
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}


/* Clear the given buffer, check it for length, and fill it with a string representation of the given vector a: */
char *vector3D_str(Vector3D *a, char *buf, uint16 len)
{
    snprintf(buf, len, "Vector3D(x=%f, y=%f, z=%f, length=%f)", a->x, a->y, a->z, vector3D_length(a));
    return buf;
}