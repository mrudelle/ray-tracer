#ifndef _SCENE_H_
#define _SCENE_H_

#include "include/object.h"
#include "include/light.h"
#include "include/transparentIntersection.h"

class Scene {
  Object *scache;
  Object *obj_list;
  Light  *light_list;
public:
  Scene(void);
  void addObject(Object &obj);
  void addLight(Light &light);
  Colour raytrace(Ray &ray, int level, TransparentIntersection* intersect_stack);
  bool shadowtrace(Ray &ray, double tlimit);
};

#endif
