#include <math.h>

#include "include/vector.h"
#include "include/vertex.h"

Vector::Vector()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

Vector::Vector(const Vertex &a, const Vertex &b){
  x = b.x-a.x;
  y = b.y-a.y;
  z = b.z-a.z;
}

void Vector::set(double px, double py, double pz)
{
  x = px;
  y = py;
  z = pz;
}

void Vector::normalise(void)
{
  double l;

  l = this->size();

  x = x/l;
  y = y/l;
  z = z/l;
}

double Vector::dot(const Vector &b)
{
  return (x*b.x)+(y*b.y)+(z*b.z);
}

float Vector::size() {
    return sqrt(x*x+y*y+z*z);
}

//Calculate the cross product of this vector and another one. the result is 
//stored in the vector result
void Vector::crossProduct(const Vector &b, Vector *result) {
    result->set(this->y*b.z - this->z*b.y,
            this->z*b.x - this->x*b.z,
            this->x*b.y - this->y*b.x);
}

bool Vector::sameDirection(const Vector& b){
     return (
        ((this->x > 0) - (this->x < 0)) == ((b.x > 0) - (b.x < 0))&
        ((this->y > 0) - (this->y < 0)) == ((b.y > 0) - (b.y < 0))&
        ((this->z > 0) - (this->z < 0)) == ((b.z > 0) - (b.z < 0))
             );
}
