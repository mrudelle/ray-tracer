/* 
 * File:   camera.cpp
 * Author: Matt
 * 
 * Created on 27 February 2014, 12:15
 */

#include "include/camera.h"
#include "include/vertex.h"
#include "include/vector.h"
#include "include/ray.h"

Camera::Camera() {
    
}

Camera::Camera(float Cd, const Vertex& Ceye, const Vector& CUp, const Vector& Clook){
    this->eye = Ceye;
    this->Up = CUp;
    this->look = Clook;
    this->d = Cd;
    
    this->w = Vector();
    w.set(-look.x, -look.y, -look.z);
    this->w.normalise();
    u = Vector();
    Up.crossProduct(w, &u);
    u.normalise();
    v = Vector();
    w.crossProduct(u, &v);
}

Ray Camera::getPerspectiveRay(float x, float y){
    Ray ray;
    ray.P.set(eye.x, eye.y, eye.z, eye.w);
    ray.D.set(u.x*x+v.x*y-w.x*d, u.y*x+v.y*y-w.y*d, u.z*x+v.z*y-w.z*d);
    //ray.D.normalise();
    //this ray has to be normalised after aplication of depth of field
    //so that we can more easily compute the intersection of the ray on
    //the focal point
    return ray;
}
