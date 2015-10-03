/* 
 * File:   Cube.cpp
 * Author: Matt
 * 
 * Created on 16. avril 2014, 21:19
 */

#include "include/cube.h"
#include "include/vertex.h"
#include "include/vector.h"
#include "include/hit.h"

Cube::Cube(float ox, float oy, float oz, float sx, float sy, float sz) {
    this->set(ox,oy, oz, sx, sy,sz);
}

 void Cube::set(float ox, float oy, float oz, float sx, float sy, float sz){
    Vector x, y, z;
    x.set(-1,0,0);
    y.set(0,-1,0);
    z.set(0,0,-1);
    planes[0] = new Plane( x, ox + sx);
    planes[1] = new Plane( x, ox);
    planes[2] = new Plane( y, oy + sy);
    planes[3] = new Plane( y, oy);
    planes[4] = new Plane( z, oz + sz);
    planes[5] = new Plane( z, oz);
    this->ox = ox;
    this->oy = oy;
    this->oz = oz;
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
 }

Cube::Cube() {
}

bool Cube::intersect(Ray& ray, Hit* h) {

	h->t = 1000000;
	bool hit = false;
	Hit closest;
	for (int i = 0; i < 6; ++i)
	{
		if (planes[i]->intersect(ray, &closest)) {
		    
			if (closest.t < h->t &&
			    closest.p.x >= ox - 0.001 && closest.p.x <= ox + sx + 0.001 &&
			    closest.p.y >= oy - 0.00001 && closest.p.y <= oy + sy + 0.00001 &&
			    closest.p.z >= oz - 0.00001 && closest.p.z <= oz + sz + 0.00001)
			{
			    h->n.set(closest.n.x, closest.n.y, closest.n.z);
			    h->obj = this;
			    h->p.set(closest.p.x, closest.p.y, closest.p.z, closest.p.w);
			    h->t = closest.t;
			    hit = true;
			}
		}
	}
	return hit;
}
