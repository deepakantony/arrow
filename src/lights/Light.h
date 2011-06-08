
#ifndef Light_h
#define Light_h

class Color;
class Point;
class Ray;
class RenderContext;
class Vector;

class Light {
 public:
  Light();
  virtual ~Light();

  virtual void preprocess();
  virtual double getLight(Color& light_color, Vector& light_direction,
                          const RenderContext& context, const Point& pos) const = 0;

 private:
  Light(const Light&);
  Light& operator=(const Light&);
};

#endif

