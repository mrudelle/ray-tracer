/* 
 * File:   plane.cpp
 * Author: Matt
 * 
 * Created on 26 February 2014, 08:59
 */

#include "include/plane.h"
#include "include/vector.h"
#include "include/ray.h"
#include "include/hit.h"

Plane::Plane(const Vertex& pa, const Vertex& pb, const Vertex& pc) {
    Vector norm;
    Vector(pc,pa).crossProduct(Vector(pb,pa), &normal);
    normal.normalise();
    float D = (-normal.x*pa.x-normal.y*pa.y-normal.z*pa.z);
    Plane(norm, D);
}

Plane::Plane(const Vector& norm, float d){
    this->normal = norm;
    this->paramD = d;
}

float Plane::A(){
    return this->normal.x;
}

float Plane::B(){
    return this->normal.y;
}

float Plane::C(){
    return this->normal.z;
}

float Plane::D(){
    return this->paramD;
}

bool Plane::intersect(Ray& ray, Hit* h) {
    float denominator = normal.dot(ray.D);
    if (denominator == 0) return false;
    Vector P;
    P.set(ray.P.x, ray.P.y, ray.P.z);
    float t = -(normal.dot(P) + D())/denominator;
    
    if (t < 0) return false;
    
    Vertex intersect;
    intersect.set(
        ray.P.x + t * ray.D.x,
        ray.P.y + t * ray.D.y,
        ray.P.z + t * ray.D.z,
        1.0);
    
    if (normal.dot(ray.D)<0){
        h->n.x = normal.x;
        h->n.y = normal.y;
        h->n.z = normal.z;
    } else {
        h->n.x = -normal.x;
        h->n.y = -normal.y;
        h->n.z = -normal.z;
    }
  
    h->n.normalise();
    h->p.x = intersect.x;
    h->p.y = intersect.y;
    h->p.z = intersect.z;
    h->p.w = intersect.w;
    h->t = t;
    h->obj = this;
    
    return true;
}


