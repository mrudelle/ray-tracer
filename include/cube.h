/* 
 * File:   Cube.h
 * Author: Matt
 *
 * Created on 16. avril 2014, 21:19
 */

#ifndef CUBE_H
#define	CUBE_H

#include "include/plane.h"
#include "include/ray.h"
#include "include/hit.h"


class Cube: public Object {
public:
    Plane *planes[6];
    float ox, oy, oz, sx, sy, sz;
    Cube(float ox, float oy, float oz, float sx, float sy, float sz);
    Cube();
    void set(float ox, float oy, float oz, float sx, float sy, float sz);
    bool intersect(Ray &ray, Hit *h);
private:

};

#endif	/* CUBE_H */

