/* 
 * File: Quadratic.cpp
 * Author: Matt
 * 
 * Created on 13. avril 2014, 10:07
 */

#include <math.h>
#include "include/quadratic.h"
#include "include/hit.h"

Quadratic::Quadratic() {
}

Quadratic::Quadratic(const Quadratic& orig) {
    this->A =  orig.A;
    this->B =  orig.B;
    this->C =  orig.C;
    this->D =  orig.D;
    this->E =  orig.E;
    this->F =  orig.F;
    this->G =  orig.G;
    this->H =  orig.H;
    this->I =  orig.I;
    this->J =  orig.J;
}

void Quadratic::set(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j){
    //F(x, y, z) = Ax2 + By2 + Cz2 + Dxy+ Exz + Fyz + Gx + Hy + Iz + J = 0
    this->A =  a;
    this->B =  b;
    this->C =  c;
    this->D =  d;
    this->E =  e;
    this->F =  f;
    this->G =  g;
    this->H =  h;
    this->I =  i;
    this->J =  j;
}

bool Quadratic::intersect(Ray &ray, Hit *h) {
    // I finally followed the steps described by this website to solve quadratic equations
    // as my attempts were unsuccessful
    //http://www.bmsc.washington.edu/people/merritt/graphics/quadrics.html
    float   Aq = A*pow(ray.D.x,2)+B*pow(ray.D.y,2)+C*pow(ray.D.z,2)+D*ray.D.x*ray.D.y+E*ray.D.x*ray.D.z+F*ray.D.y*ray.D.z,
            Bq = 2*A*ray.P.x*ray.D.x+2*B*ray.P.y*ray.D.y+2*C*ray.P.z*ray.D.z+D*(ray.P.x*ray.D.y+ray.P.y*ray.D.x)+E*(ray.P.x*ray.D.z+ray.P.z*ray.D.x)+F*(ray.P.y*ray.D.z+ray.D.y*ray.P.z)+G*ray.D.x+H*ray.D.y+I*ray.D.z,
            Cq = A*pow(ray.P.x,2)+B*pow(ray.P.y,2)+C*pow(ray.P.z,2)+D*ray.P.x*ray.P.y+E*ray.P.x*ray.P.z+F*ray.P.y*ray.P.z+G*ray.P.x+H*ray.P.y+I*ray.P.z+J,
            t;

    if (Aq != 0.0) {
            if ((Bq*Bq - 4*Aq*Cq) < 0.0) { return false; }
            float 	t0 = (-Bq-sqrt(Bq*Bq-4*Aq*Cq))/(2*Aq),
                            t1 = (-Bq+sqrt(Bq*Bq-4*Aq*Cq))/(2*Aq);
            t = t0 < t1 && t0 >= 0? t0 : t1;
    } else {
            t = -Cq/Bq;
    }

    if (t < 0.0) {return false;}

    h->t = t;
    // for here D has to be already normalized
    h->p.x = ray.P.x + ray.D.x * t;
    h->p.y = ray.P.y + ray.D.y * t;
    h->p.z = ray.P.z + ray.D.z * t;
    h->p.w = 1.0;
    h->n.x = 2*A*h->p.x + D*h->p.y + E*h->p.z + G;
    h->n.y = 2*B*h->p.y + D*h->p.x + F*h->p.z + H;
    h->n.z = 2*C*h->p.z + E*h->p.x + F*h->p.y + I;
    h->n.normalise();

    //Change normal's sens if they are opposit to the incoming ray
    if (h->n.dot(ray.D)>0) {
        h->n.x = -h->n.x;
    	h->n.y = -h->n.y;
        h->n.z = -h->n.z;
    }

    h->obj = this;

    return true;
}

Quadratic::~Quadratic() {
}

