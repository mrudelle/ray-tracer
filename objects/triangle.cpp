/* 
 * File:   triangle.cpp
 * Author: Matt
 * 
 * Created on 20 February 2014, 14:37
 */
#include <math.h>
#include "include/triangle.h"

Triangle::Triangle(const Vertex &tpa, const Vertex &tpb, const Vertex &tpc) {
    ta = tpa;
    tb = tpb;
    tc = tpc;
}

bool Triangle::intersect(Ray &ray, Hit *h) {
    Vector normal;
    Vector(tc,ta).crossProduct(Vector(tb,ta), &normal);
    normal.normalise();
    float D = (-normal.x*ta.x-normal.y*ta.y-normal.z*ta.z);
    
    //Plane formula: Ax+By+Cz+D=0
    //where normal=[A, B, C]
    
    //Plain intersection:
    float denominator = normal.dot(ray.D);
    if (denominator == 0) return false;
    Vector P;
    P.set(ray.P.x, ray.P.y, ray.P.z);
    float t = -(normal.dot(P) + D)/denominator;
    
    if (t < 0) return false;
    
    Vertex intersect;
    intersect.set(
        ray.P.x + t * ray.D.x,
        ray.P.y + t * ray.D.y,
        ray.P.z + t * ray.D.z,
        1.0);
            
    
    //Does the point belongs to the triangle: 
    Vector cpa, cpb, cpc;
    Vector(intersect, ta).crossProduct(Vector(tb, ta), &cpa);
    Vector(intersect, tb).crossProduct(Vector(tc, tb), &cpb);
    Vector(intersect, tc).crossProduct(Vector(ta, tc), &cpc);
    
    if(!(cpa.sameDirection(cpb)&cpb.sameDirection(cpc))){
        return false;
    }
    
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



