

#include "Instance.h"
#include "rtengine/Ray.h"

Instance::Instance()
: Object()
{
}

Instance::Instance(Object *obj)
: Object(), obj(obj)
{
}

Instance::~Instance() {
	if(obj) {
		delete obj;
		obj = NULL;
	}
}

void Instance::setObject(Object *obj) {
	this->obj = obj;
	this->obj->setInstance(true);
	this->obj->setTransMatrix(transMatrix);
	this->obj->setInvTransMatrix(invTransMatrix);
}

void Instance::getBounds(BoundingBox& bbox) const
{
}

void Instance::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	Ray invRay(invTransMatrix*ray.origin(), invTransMatrix*ray.direction());
	obj->intersect(hit,context,invRay);
}

void Instance::translate(const Vector& trans) {
	Matrix tempMatInv;
	tempMatInv.m[0][3] = -trans.x();
	tempMatInv.m[1][3] = -trans.y();
	tempMatInv.m[2][3] = -trans.z();
	invTransMatrix = invTransMatrix * tempMatInv;
	
	Matrix tempMatTrans;
	tempMatTrans.m[0][3] = trans.x();
	tempMatTrans.m[1][3] = trans.y();
	tempMatTrans.m[2][3] = trans.z();
	
	transMatrix = tempMatTrans * transMatrix; 
}

void Instance::translate(const double dx, const double dy, const double dz) {
	Matrix tempMatInv;
	tempMatInv.m[0][3] = -dx;
	tempMatInv.m[1][3] = -dy;
	tempMatInv.m[2][3] = -dz;
	invTransMatrix = invTransMatrix * tempMatInv;
	
	Matrix tempMatTrans;
	tempMatTrans.m[0][3] = dx;
	tempMatTrans.m[1][3] = dy;
	tempMatTrans.m[2][3] = dz;
	
	transMatrix = tempMatTrans * transMatrix; 
}

void Instance::scale(const Vector& s) {
	Matrix	scalingMatInv;
	
	scalingMatInv.m[0][0] = 1.0/s.x();
	scalingMatInv.m[1][1] = 1.0/s.y();
	scalingMatInv.m[2][2] = 1.0/s.z();

	invTransMatrix = invTransMatrix * scalingMatInv;			

	Matrix	scalingMat;
	
	scalingMat.m[0][0] = s.x();
	scalingMat.m[1][1] = s.y();
	scalingMat.m[2][2] = s.z();
	
	transMatrix = scalingMat * transMatrix; 
}

void Instance::scale(const double a, const double b, const double c) {
	Matrix	scalingMatInv;
	
	scalingMatInv.m[0][0] = 1.0/a;
	scalingMatInv.m[1][1] = 1.0/b;
	scalingMatInv.m[2][2] = 1.0/c;

	invTransMatrix = invTransMatrix * scalingMatInv;			

	Matrix	scalingMat;
	
	scalingMat.m[0][0] = a;
	scalingMat.m[1][1] = b;
	scalingMat.m[2][2] = c;
	
	transMatrix = scalingMat * transMatrix; 
}

void Instance::rotateX(const double r) {
	double sinTheta = sin(r * M_PI / 180);
	double cosTheta = cos(r * M_PI / 180);
	
	Matrix rotMatInv;
	rotMatInv.m[1][1] = cosTheta;
	rotMatInv.m[1][2] = sinTheta;   	
	rotMatInv.m[2][1] = -sinTheta;  
	rotMatInv.m[2][2] = cosTheta;
	invTransMatrix = invTransMatrix * rotMatInv;	   	
	
	Matrix rotMat;
	rotMat.m[1][1] = cosTheta;
	rotMat.m[1][2] = -sinTheta;
	rotMat.m[2][1] = sinTheta;
	rotMat.m[2][2] = cosTheta;
	transMatrix = rotMat * transMatrix;
}

void Instance::rotateY(const double r) {
	double sinTheta = sin(r * M_PI / 180);
	double cosTheta = cos(r * M_PI / 180);
	
	Matrix rotMatInv;
	rotMatInv.m[0][0] = cosTheta;   
	rotMatInv.m[0][2] = -sinTheta;  
	rotMatInv.m[2][0] = sinTheta;
	rotMatInv.m[2][2] = cosTheta;
	invTransMatrix = invTransMatrix * rotMatInv;	   	
	
	Matrix rotMat;
	rotMat.m[0][0] = cosTheta;   
	rotMat.m[0][2] = sinTheta;  
	rotMat.m[2][0] = -sinTheta;
	rotMat.m[2][2] = cosTheta;
	transMatrix = rotMat * transMatrix;
}

void Instance::rotateZ(const double r) {
	double sinTheta = sin(r * M_PI / 180);
	double cosTheta = cos(r * M_PI / 180);
	
	Matrix rotMatInv;
	rotMatInv.m[0][0] = cosTheta;
	rotMatInv.m[0][1] = sinTheta;   	
	rotMatInv.m[1][0] = -sinTheta;  
	rotMatInv.m[1][1] = cosTheta;
	invTransMatrix = invTransMatrix * rotMatInv;	   	
	
	Matrix rotMat;
	rotMat.m[0][0] = cosTheta;
	rotMat.m[0][1] = -sinTheta;   	
	rotMat.m[1][0] = sinTheta;  
	rotMat.m[1][1] = cosTheta;
	transMatrix = rotMat * transMatrix;	
}

void Instance::shear(const Matrix& m) {
	Matrix shearMatInv;
	
	// calculate the discriminant
	double disc = 1.0 	- m.m[1][0]*m.m[0][1] 
		- m.m[2][0]*m.m[0][2]  - m.m[2][1]*m.m[1][2] 
		+ m.m[1][0]*m.m[2][1]*m.m[0][2] + m.m[2][0]*m.m[0][1]*m.m[2][1];
	
	shearMatInv.m[0][0] = 1.0 - m.m[2][1]*m.m[1][2];
	shearMatInv.m[1][1] = 1.0 - m.m[2][0]*m.m[0][2];
	shearMatInv.m[2][2] = 1.0 - m.m[1][0]*m.m[0][1];
	shearMatInv.m[3][3] = disc;
	
	shearMatInv.m[0][1] = -m.m[1][0] + m.m[2][0]*m.m[1][2];
	shearMatInv.m[0][2] = -m.m[2][0] + m.m[1][0]*m.m[2][1];
	
	shearMatInv.m[1][0] = -m.m[0][1] + m.m[2][1]*m.m[0][2];
	shearMatInv.m[1][2] = -m.m[2][1] + m.m[2][0]*m.m[0][1];
	
	shearMatInv.m[2][0] = -m.m[0][2] + m.m[0][1]*m.m[1][2];
	shearMatInv.m[2][1] = -m.m[1][2] + m.m[1][0]*m.m[0][2] ;

	shearMatInv = shearMatInv / disc;
	
	invTransMatrix = invTransMatrix * shearMatInv;	
	
	transMatrix = m * transMatrix; 
}
