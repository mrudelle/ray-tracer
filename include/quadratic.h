/* 
 * File:   Quadratic.h
 * Author: Matt
 *
 * Created on 13. avril 2014, 10:07
 */

#ifndef QUADRATIC_H
#define	QUADRATIC_H

#include "include/object.h"

class Quadratic: public Object  {
public:
    //F(x, y, z) = Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J = 0
    float A,B,C,D,E,F,G,H,I,J;
    Quadratic();
    void set(float A, float B, float C, float D, float E, float F, float G, float H, float I, float J);
    bool intersect(Ray &ray, Hit *h);
    Quadratic(const Quadratic& orig);
    virtual ~Quadratic();
private:

};

#endif	/* QUADRATIC_H */

