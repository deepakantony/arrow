
#include "Box.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>
#include <malloc.h>

Box::Box(Material* material, const Point& corner1, const Point& corner2)
:Primitive(material)
{
	this->corner1[0] = corner1.x(); 
	this->corner1[1] = corner1.y(); 
	this->corner1[2] = corner1.z();
	this->corner2[0] = corner2.x(); 
	this->corner2[1] = corner2.y(); 
	this->corner2[2] = corner2.z();
}

Box::~Box()
{
}

void Box::getBounds(BoundingBox& bbox) const
{
}

void Box::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	double ox = ray.origin().x(), oy = ray.origin().y(), oz = ray.origin().z();
	double dx = ray.direction().x(), dy = ray.direction().y(), dz = ray.direction().z();

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;
	
	double tmin;

	double a = 1.0/dx;

	if(a>=0) {
		tx_min = (corner1[0] - ox) * a;
		tx_max = (corner2[0] - ox) * a;
	}
	else {
		tx_min = (corner2[0] - ox) * a;
		tx_max = (corner1[0] - ox) * a;
	}
	
	double b = 1.0/dy;

	if(b>=0) {
		ty_min = (corner1[1] - oy) * b;
		ty_max = (corner2[1] - oy) * b;
	}
	else {
		ty_min = (corner2[1] - oy) * b;
		ty_max = (corner1[1] - oy) * b;
	}
	
	double c = 1.0/dz;

	if(c>=0) {
		tz_min = (corner1[2] - oz) * c;
		tz_max = (corner2[2] - oz) * c;
	}
	else {
		tz_min = (corner2[2] - oz) * c;
		tz_max = (corner1[2] - oz) * c;
	}
	
	double tlarge, tsmall;
	int inFace, outFace;

	// largest t entering value
	if(tx_min > ty_min) {
		tlarge = tx_min;
		inFace = (a >= 0.0) ? 0 : 3;
	}
	else {
		tlarge = ty_min;
		inFace = (b >= 0.0) ? 1 : 4;
	}
	if(tz_min > tlarge) {
		tlarge = tz_min;
		inFace = (c >= 0.0) ? 2 : 5;
	}
	
	// smallest t exiting value
	if(tx_max < ty_max) {
		tsmall = tx_max;
		outFace = (a >= 0.0) ? 3 : 0;
	}
	else {
		tsmall = ty_max;
		outFace = (b >= 0.0) ? 4 : 1;
	}
	if(tz_max < tsmall) {
		tsmall = tz_max;
		outFace = (c >= 0.0) ? 5 : 2;
	}
	
	if(tlarge < tsmall && tsmall > kEpsilon) {
		if(tlarge > kEpsilon) {
			tmin = tlarge;
			//updateFacehit(inFace);
		}
		else {
			tmin = tsmall;
			//updateFacehit(outFace);
		}
		
		hit.hit(tmin, this, matl);
	}
}

void Box::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	
	double ox = ray.origin().x(), oy = ray.origin().y(), oz = ray.origin().z();
	double dx = ray.direction().x(), dy = ray.direction().y(), dz = ray.direction().z();

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;
	
	double tmin;

	double a = 1.0/dx;

	if(a>=0) {
		tx_min = (corner1[0] - ox) * a;
		tx_max = (corner2[0] - ox) * a;
	}
	else {
		tx_min = (corner2[0] - ox) * a;
		tx_max = (corner1[0] - ox) * a;
	}
	
	double b = 1.0/dy;

	if(b>=0) {
		ty_min = (corner1[1] - oy) * b;
		ty_max = (corner2[1] - oy) * b;
	}
	else {
		ty_min = (corner2[1] - oy) * b;
		ty_max = (corner1[1] - oy) * b;
	}
	
	double c = 1.0/dz;

	if(c>=0) {
		tz_min = (corner1[2] - oz) * c;
		tz_max = (corner2[2] - oz) * c;
	}
	else {
		tz_min = (corner2[2] - oz) * c;
		tz_max = (corner1[2] - oz) * c;
	}
	
	double tlarge, tsmall;
	int inFace, outFace;

	// largest t entering value
	if(tx_min > ty_min) {
		tlarge = tx_min;
		inFace = (a >= 0.0) ? 0 : 3;
	}
	else {
		tlarge = ty_min;
		inFace = (b >= 0.0) ? 1 : 4;
	}
	if(tz_min > tlarge) {
		tlarge = tz_min;
		inFace = (c >= 0.0) ? 2 : 5;
	}
	
	// smallest t exiting value
	if(tx_max < ty_max) {
		tsmall = tx_max;
		outFace = (a >= 0.0) ? 3 : 0;
	}
	else {
		tsmall = ty_max;
		outFace = (b >= 0.0) ? 4 : 1;
	}
	if(tz_max < tsmall) {
		tsmall = tz_max;
		outFace = (c >= 0.0) ? 5 : 2;
	}
	
	if(tlarge < tsmall && tsmall > kEpsilon) {
		if(tlarge > kEpsilon) {
			tmin = tlarge;
			switch(inFace) {
			case 0: normal = Vector(-1, 0, 0); break;
			case 1: normal = Vector(0, -1, 0); break;
			case 2: normal = Vector(0, 0, -1); break;
			case 3: normal = Vector(1, 0, 0); break;
			case 4: normal = Vector(0, 1, 0); break;
			case 5: normal = Vector(0, 0, 1); break;
			}
		}
		else {
			tmin = tsmall;
			//updateFacehit(outFace);
			
			switch(outFace) {
			case 0: normal = Vector(-1, 0, 0); break;
			case 1: normal = Vector(0, -1, 0); break;
			case 2: normal = Vector(0, 0, -1); break;
			case 3: normal = Vector(1, 0, 0); break;
			case 4: normal = Vector(0, 1, 0); break;
			case 5: normal = Vector(0, 0, 1); break;
			}			
		}	
	}

}

void Box::updateFacehit(int faceHit) {
	this->faceHit = faceHit;
}
