#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "include/colour.h"

class Material {
 public:
  Colour ka; //ambiant
  Colour kd; //difuse
  Colour ks; //specular
  Colour kr; //reflective
  Colour kt; //transparent
  double refractionIndex;
  double n; //phong specular power term
  void setPhong(Colour *c, float ka, float kd, float ks, float kr, float kt, double refIndex, double n);
  void setPhong(float r, float g, float b, float ka, float kd, float ks, float kr, float kt, double refIndex, double n);
};

#endif
