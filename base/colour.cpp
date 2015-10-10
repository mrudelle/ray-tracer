#include "include/colour.h"

Colour::Colour()
{
  red   = 0.0;
  green = 0.0;
  blue  = 0.0;
  alpha = 0.0;
}

// defines the base color (primarily of the sky)
void Colour::clear(void)
{
  red   = 0.90196;
  green = 0.90196;
  blue  = 0.90196;
  alpha = 1.0;
}

// defines the black color (primarily of the sky)
void Colour::blacken(void)
{
  red   = 0.0;
  green = 0.0;
  blue  = 0.0;
  alpha = 1.0;
}

void Colour::set(float pred, float pgreen, float pblue, float palpha)
{
  red   = pred;
  green = pgreen;
  blue  = pblue;
  alpha = palpha;
}

float Colour::getRed(void)
{
  return red;
}

float Colour::getGreen(void)
{
  return green;
}

float Colour::getBlue(void)
{
  return blue;
}

float Colour::getAlpha(void)
{
  return alpha;
}
