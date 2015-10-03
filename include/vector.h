#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "include/vertex.h"

class Vector {
 public:
  double x;
  double y;
  double z;
  Vector(void);
  Vector(const Vertex &a, const Vertex &b);
  void set(double x, double y, double z);
  void normalise(void);
  double dot(const Vector &b);
  float size();
  void crossProduct(const Vector &b, Vector *result);
  bool sameDirection(const Vector &b);
};


#endif
