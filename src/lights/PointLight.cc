
#include "PointLight.h"

PointLight::PointLight(const Point& position, const Color& color)
  : position(position), color(color)
{
}

PointLight::~PointLight()
{
}

void PointLight::preprocess()
{
}

double PointLight::getLight(Color& light_color, Vector& light_direction,
                            const RenderContext&, const Point& hitpos) const
{
  light_color = color;
  Vector dir = position-hitpos;
  double len = dir.normalize();
  light_direction = dir;
  return len;
}
