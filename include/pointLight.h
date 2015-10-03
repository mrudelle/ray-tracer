/* 
 * File:   PointLight.h
 * Author: Matt
 *
 * Created on 17. avril 2014, 10:28
 */

#ifndef POINTLIGHT_H
#define	POINTLIGHT_H

#include "include/light.h"

class PointLight :public Light{
public:
    Vertex P;
    Vector D;
    Colour intensity;
    double eCoeff;
    PointLight(Vertex &p, Vector &d, Colour &c, float intens, double eCoeff);
    virtual void getLightProperties(Vertex &pos, Vector *ldir, Colour *i);
    virtual float distanceToSource(Vertex& pos);

private:

};

#endif	/* POINTLIGHT_H */

