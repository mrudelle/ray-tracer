/* 
 * File:   Transformation.h
 * Author: Matt
 *
 * Created on 26 March 2014, 18:48
 */

#ifndef TRANSFORMATION_H
#define	TRANSFORMATION_H

#include "include/vertex.h"
#include "include/vector.h"
#include "include/ray.h"
#include "include/hit.h"

class Transformation{
public:
    float A, B, C, D,
        E, F, G, H, 
        I, J, K, L;
    Transformation* t_next;
    
    Transformation();
    void link(Transformation *obj);
    Transformation *next(void);
    void set(float a, float b, float c, float d,
                float e, float f, float g, float h,
                float i, float j, float k, float l);
    void rotationx(float alpha);
	void rotationy(float alpha);
	void rotationz(float alpha);
    void translation(float x, float y, float z);
    void scale(float x, float y, float z);
    void identity();
    
    Vertex transform(Vertex v);
    Vector transform(Vector v);
    Ray transform(Ray r);
    Hit transform(Hit h);
    Transformation composeWith(const Transformation t);
    Transformation inverse();
};

#endif	/* TRANSFORMATION_H */

