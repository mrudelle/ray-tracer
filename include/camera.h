/* 
 * File:   camera.h
 * Author: Matt
 *
 * Created on 27 February 2014, 12:15
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "include/vector.h"
#include "include/vertex.h"
#include "include/ray.h"

class Camera {
public:
    float d;
    Vertex eye;
    Vector Up, look;
    
    Vector w, u, v;
    Camera();
    Camera(float d, const Vertex& eye, const Vector& Up, const Vector& look);
    Ray getPerspectiveRay(float x, float y);
};

#endif	/* CAMERA_H */

