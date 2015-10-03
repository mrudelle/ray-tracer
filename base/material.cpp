#include <math.h>

#include "include/material.h"

// allowss an easier creation of Materials
void Material::setPhong(float r, float g, float b, 
    float ka, float kd, float ks, float kr, float kt, 
    double refIndex, double n)
{
    // ambient color component
    this->ka.set(r * ka, g * ka, b * ka, 1.0);

    // diffuse reflection color factor
    this->kd.set(r * kd, g * kd, b * kd, 1.0);

    // specular reflection color factor
    this->ks.set(ks, ks, ks, 1.0);
    
    // refraction color factor
    this->kr.set(kr, kr, kr, 1.0);

    // transparency color factor
    this->kt.set(kt, kt, kt, 1.0);

    this->n = n;
    this->refractionIndex = refIndex;
}

// allowss an easier creation of Materials
void Material::setPhong(Colour *c, 
    float ka, float kd, float ks, float kr, float kt, 
    double refIndex, double n)
{
    this->setPhong(c->red, c->green, c->blue, ka, kd, ks, kr, kt, refIndex, n);
}