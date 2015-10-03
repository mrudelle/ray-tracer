// Object - The base class for objects.

#include <math.h>

#include "include/object.h"

Object::Object(void)
{
    this->obj_transform = new Transformation();
    this->obj_transform->identity();
}

Object::~Object(void)
{
    delete this->obj_transform;
}

void Object::link(Object *obj)
{
  obj_next = obj;
}

Object *Object::next(void)
{
  return obj_next;
}

void Object::setMaterial(Material *m)
{
  obj_mat = m;
}

void Object::setTransformation(const Transformation *t)
{
    *obj_transform = *t;
}

Colour Object::getColour()
{
  Colour a;
  return a;
}

bool Object::sintersect(Ray &ray, Hit *h, double tl)
{
  bool res;
  Hit nh;

  if (this->intersect(ray, &nh) == true)
  {
    if (nh.t > tl) return false;

    *h = nh;

    return true;
  }

  return false;
}

bool Object::transformedintersect(Ray &ray, Hit *h, float tl)
{
    bool res;
    Hit nh;
    
    Transformation inverse = this->obj_transform->inverse();
    Ray robj; // ray in the object universe (we apply the inverse transformation)
    robj.D = inverse.transform(ray.D);
    robj.P = inverse.transform(ray.P);
    
    //coefficient to transform the distances for one reference system to another
    float coeff = robj.D.size();
    robj.D.normalise();
    
    //apply the inverse transfo to the ray
    if (this->intersect(robj, &nh))
    {
        nh.t = nh.t/coeff;
        
        if (nh.t > tl) return false;

            // the transformation of normal is slightly special:
            // see: http://www.songho.ca/opengl/gl_normaltransform.html
            // we compute ((M^-1)^T)
            inverse.set(
                inverse.A, inverse.E, inverse.I, 0,
                inverse.B, inverse.F, inverse.G, 0,
                inverse.C, inverse.G, inverse.K, 0);

            nh.n = inverse.transform(nh.n);
            nh.p = this->obj_transform->transform(nh.p);
            *h = nh;
        return true;
    }

  return false;
}
