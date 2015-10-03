/* 
 * File:   plane.h
 * Author: Matt
 *
 * Created on 26 February 2014, 08:59
 */

#ifndef PLANE_H
#define	PLANE_H

#include "include/vector.h"
#include "include/ray.h"
#include "include/hit.h"
#include "include/object.h"

class Plane: public Object {
    Vector normal;
    float paramD;
public:
    Plane(const Vertex &pa, const Vertex &pb, const Vertex &pc);
    Plane(const Vector &norm, float d);
    float A();
    float B();
    float C();
    float D();
    bool intersect(Ray &ray, Hit *h);
};

#endif	/* PLANE_H */

