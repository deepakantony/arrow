#ifndef HEIGHTFIELD_H_
#define HEIGHTFIELD_H_

#include <string>
#include "Primitive.h"
#include "utils/Point.h"
#include "utils/Vector.h"

using namespace std;

class Ray;

class Heightfield : public Primitive {
 public:
  Heightfield(Material* material, const string file, const Point& corner1, const Point& corner2);
  Heightfield(Material* material, const Point& corner1, const Point& corner2);
  virtual ~Heightfield();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	string file;
	Point corner1, corner2;
	int nx, ny;
	float maxz, minz;
	float **data;
	Vector diagonal, cellsize;
	/*
	string file;
	Point minExtent, maxExtent;//corner1, corner2;
	int nx, ny;
	float maxz, minz;
	float **data;
	Vector D, cellSize; //diagonal, cellsize;
	double tN, tF;*/
};

#endif /*HEIGHTFIELD_H_1*/
