/* 
 * File:   PointLight.cpp
 * Author: Matt
 * 
 * Created on 17. avril 2014, 10:28
 */

#include <math.h>
#include "include/pointLight.h"
#include "include/vector.h"
#include "include/colour.h"
#include "include/camera.h"
#include "include/directional_light.h"

PointLight::PointLight(Vertex &p, Vector &d, Colour &c, float intens, double eCoeff) {
    D.set(d.x, d.y, d.z);
    D.normalise();
    P.set(p.x, p.y, p.z, p.w);
    intensity.set(c.red * intens, c.green * intens, c.blue * intens, c.alpha);
    this->eCoeff = eCoeff;
}

void PointLight::getLightProperties(Vertex &pos, Vector *ldir, Colour *i)
{
  // the direction is always the same (light is infinitely far away)
    ldir->set(
	this->P.x-pos.x,
	this->P.y-pos.y,
	this->P.z-pos.z);
    float dist2 = ldir->size();
    dist2 = dist2*dist2;
    ldir->normalise();
    
    // I'll follow the repartition of specular lightning (see graph 15.4 of
    // ray tracing from the ground up)
    double dirCoeff ;
    if (this->D.x != 0 || this->D.y != 0 || this->D.z != 0)
    {
	dirCoeff = -ldir->dot(this->D);
	if (dirCoeff < 0.0) {
	    dirCoeff = 0.0;
	}
	dirCoeff = pow(dirCoeff, this->eCoeff);
    }
    else
    {
	dirCoeff = 1.0;
    }

    // the intensity is always the same (not dependent on where it's going
    i->set(intensity.getRed()*dirCoeff/dist2,intensity.getGreen()*dirCoeff/dist2,intensity.getBlue()*dirCoeff/dist2,intensity.getAlpha());
  
}

float PointLight::distanceToSource(Vertex& pos)
{
    Vector v;
    v.set(
	this->P.x-pos.x,
	this->P.y-pos.y,
	this->P.z-pos.z);
    return v.size();
}
