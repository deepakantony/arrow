
#ifndef PinholeCamera_h
#define PinholeCamera_h

#include "Camera.h"
#include "Point.h"
#include "Vector.h"

class PinholeCamera : public Camera {
 public:
  PinholeCamera(const Point& eye, const Point& lookat, const Vector& up, double hfov);
  virtual ~PinholeCamera();
  
  virtual void preprocess(double aspect_ratio);
  virtual void makeRay(Ray& ray, const RenderContext& context, double x, double y) const;

 private:
  PinholeCamera(const PinholeCamera&);
  PinholeCamera& operator=(const PinholeCamera&);

  Point eye;
  Point lookat;
  Vector up;
  double hfov;

  Vector u;
  Vector v;
  Vector lookdir;
};

#endif

