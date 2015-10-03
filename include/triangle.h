/* 
 * File:   triangle.h
 * Author: Matt
 *
 * Created on 20 February 2014, 14:37
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "include/object.h"

class Triangle: public Object {
    Vertex ta;
    Vertex tb;
    Vertex tc;
    public:
        Triangle(const Vertex &tpa, const Vertex &tpb, const Vertex &tpc);
        bool intersect(Ray &ray, Hit *h);
private:
};

#endif	/* TRIANGLE_H */

