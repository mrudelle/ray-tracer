#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "include/vertex.h"
#include "include/vector.h"
#include "include/colour.h"
#include "include/ray.h"
#include "include/hit.h"
#include "include/colour.h"
#include "include/material.h"
#include "include/transformation.h"

class Object {
  Object *obj_next;
  Transformation* obj_transform;
 public:
  Material *obj_mat;
  Object(void);
  ~Object(void);
  void link(Object *obj);
  Object *next(void);
  void setMaterial(Material *m);
  void setTransformation(const Transformation *t);
  Colour getColour();
  virtual bool intersect(Ray &ray, Hit *h) { return false; }
  virtual bool sintersect(Ray &ray, Hit *h, double tl);
  virtual bool transformedintersect(Ray &ray, Hit *h, float t1);
};

#endif
