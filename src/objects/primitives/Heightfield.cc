
#include "Heightfield.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
//#include <map.h>
#include <float.h>

using namespace std;

Heightfield::Heightfield(Material* material, const string file, const Point& corner1, const Point& corner2)
:Primitive(material), file(file), corner1(corner1), corner2(corner2)
{
	// Read the heightfield file
	ifstream datafile(file.c_str(), ios::in|ios::binary);
	if(!datafile) {
		cerr << "Heightfield data file not found!" << file << endl;
		exit(1);
	}
	nx = 206; // keystone
	ny = 209;
	//nx = 294; // santa barbara
	//ny = 327;
	//nx = 305; // wendover
	//ny = 308;
	//nx = 2364; // SLC
	//ny = 2346;
	//datafile >> nx >> ny >> minz >> maxz;
	
	
	data = new float*[nx+1];
	float* p = new float[(nx+1)*(ny+1)];
	for(int i = 0;i <= nx;i++) {
		data[i] = p+i*(ny+1);
		//datafile.read(reinterpret_cast<char*>(data[i]), sizeof(float)*(ny+1));
	}
	datafile.read(reinterpret_cast<char*>(data[0]), sizeof(float)*(nx+1)*(ny+1));
	minz = FLT_MIN;
	maxz = -FLT_MAX;
	for(int i = 0; i <= nx; i++) {
		for(int j = 0; j <= ny; j++) {
			if(data[i][j] < minz)
				minz = data[i][j];
			if(data[i][j] > maxz)
				maxz = data[i][j];
		}
	}
	
	// Scale the data
	for(int i = 0; i <= nx; i++) {
		for(int j = 0; j <= ny; j++) {
			data[i][j] = data[i][j] / maxz;
			//if(data[i][j] < 0.5) data[i][j] = 0.5;
		}
	}
	
	minz = FLT_MIN;
	maxz = -FLT_MAX;
	for(int i = 0; i <= nx; i++) {
		for(int j = 0; j <= ny; j++) {
			if(data[i][j] < minz)
				minz = data[i][j];
			if(data[i][j] > maxz)
				maxz = data[i][j];
		}
	}
	/*
	//nx=200;
  //ny=200;
  data = new float*[nx+1];
  float* p = new float[(nx+1)*(ny+1)];
  for(int i=0;i<=nx;i++)
    data[i] = p+i*(ny+1);
   maxz = -1.e10;
   minz = 1.e10;
  for(int i=0;i<=nx;i++){
    double x = double(i)/nx*2-1;
    for(int j=0;j<=ny;j++){
      double y = double(j)/ny*2-1;
      data[i][j] = 0.5*sin(x*10.0) + 0.1*(1.0+0.5*sin(x*y*64.0))*cos(y*10.0) + 1.5;
      if(data[i][j] < minz)
        minz = data[i][j];
      if(data[i][j] > maxz)
        maxz = data[i][j];
    }
  }*/
	
	/*if(!datafile) {
		cerr << "Heightfield data could not be read! Filename :" << file << endl;
		exit(1);
	}*/
	
	//if (minz < corner1.z())
		this->corner1 = Point(corner1.x(), corner1.y(), minz-0.1);

	if (maxz > corner2.z())
		this->corner2 = Point(corner2.x(), corner2.y(), maxz);
	
	// Computing some derived values
	diagonal = Vector(corner2 - corner1);
	cellsize = diagonal/Vector(nx, ny, 1);
}

Heightfield::~Heightfield()
{
}

void Heightfield::getBounds(BoundingBox& bbox) const
{
	bbox.extend(corner1);
	bbox.extend(corner2);
}

void Heightfield::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	Vector rayDir = ray.direction();
	Vector rayInv = rayDir.inverse();
	Point origin = ray.origin(); 
	
	// Computation of tnear and tfar using the ray box intersection
	Vector vCorner1 = (corner1 - origin) * rayInv;
	Vector vCorner2 = (corner2 - origin) * rayInv;
	Vector vMin = Min(vCorner1, vCorner2);
	Vector vMax = Max(vCorner1, vCorner2);
	double tnear = vMin.maxComponent();
	double tfar = vMax.minComponent();
	if(tnear >= tfar) return;
	if(tfar < 1.e-6) return;
	if(tnear < 0) tnear = 0.0;

	// Computation of the lattice coordinates of the near point
	Point point = origin + tnear * rayDir; // world space
	int lx = (int)((point.x() - corner1.x())/cellsize.x());
	lx = lx < 0 ? 0 : lx >= nx ? nx - 1 : lx;
	int ly = (int)((point.y() - corner1.y())/cellsize.y());
	ly = ly < 0 ? 0 : ly >= ny ? ny - 1 : ly;
	
    // Determination of how ray marching changes index
    int dix = diagonal.x() * rayDir.x() > 0 ? 1 : -1;
    int diy = diagonal.y() * rayDir.y() > 0 ? 1 : -1;
    int stopx = diagonal.x() * rayDir.x() > 0 ? nx : -1;
    int stopy = diagonal.y() * rayDir.y() > 0 ? ny : -1;

	// Determination of how t value changes with ray marching
	double dtdx = Abs(cellsize.x() * rayInv.x());
	double dtdy = Abs(cellsize.y() * rayInv.y());

	// Determination of the far edges of the cell
	double farx, fary;
	if(dix == 1) farx = (lx+1)*cellsize.x()+corner1.x();
	else farx = lx*cellsize.x()+corner1.x();
	if(diy == 1) fary = (ly+1)*cellsize.y()+corner1.y();
	else fary = ly*cellsize.y()+corner1.y();
	
	// Determination of t value of far slabs
	double tnextx = (farx - origin.x()) * rayInv.x();
	double tnexty = (fary - origin.y()) * rayInv.y();
    
    // Compute the range of Z values
    double zenter = origin.z() + tnear * rayDir.z();
    while(1/*tnear < tfar*/) {
    	double texit = Min(tnextx, tnexty);
    	double zexit = origin.z() + texit * rayDir.z();
    	
		float datamin = Min(Min(data[lx][ly], data[lx+1][ly]), Min(data[lx][ly+1], data[lx+1][ly+1]));
		float datamax = Max(Max(data[lx][ly], data[lx+1][ly]), Max(data[lx][ly+1], data[lx+1][ly+1]));
		float zmin = Min(zenter, zexit);
		float zmax = Max(zenter, zexit);
    	if(zmin >= datamax || zmax <= datamin || zmin >= zmax || datamin >= datamax) {
    	 	// march to next cell
    		if(tnextx < tnexty) {
    			tnear = tnextx;
    			tnextx += dtdx;
    			lx += dix;
    			if(lx == stopx) break;
    		}
    		else {
    			tnear = tnexty;
    			tnexty += dtdy;
    			ly += diy;
    			if(ly == stopy) break;
    		}
    	}
    	else {
			Point C = corner1 + Vector(lx, ly, 0) * cellsize;
			Point E = origin + tnear * rayDir;
			Vector EC = E - C;
			
			double Sx = EC.x()/cellsize.x();
			double Sy = EC.y()/cellsize.y();
			double Dx = rayDir.x()/cellsize.x();
			double Dy = rayDir.y()/cellsize.y();
			
			double Zc = data[lx][ly];
			double Zu = data[lx+1][ly] - data[lx][ly];
			double Zv = data[lx][ly+1] - data[lx][ly];
			double Zuv = data[lx+1][ly+1] - data[lx+1][ly] -data[lx][ly+1] + data[lx][ly];
			
			double a = Dx*Dy*Zuv;
			double b = -rayDir.z() + Sx*Dy*Zuv + Dx*Sy*Zuv + Dy*Zv + Dx*Zu;
			double c = -E.z() + Sx*Sy*Zuv + Sy*Zv + Sx*Zu + Zc;
			
			double disc = b * b - 4 * a * c;

			if(a == 0) {
				double tcell = -c/b;
				if(tcell >= 0 && tnear + tcell <= texit) {
					if(hit.hit(tnear+tcell, this, matl)) {
						*hit.getScratchpad<Vector>() = Vector(lx, ly, 0);
						break;
					}
				}
				
			}
			else{
				if(disc > 0){
					double root = sqrt(disc);
					double tcell1 = (-b + root)/(2*a);
					double tcell2 = (-b - root)/(2*a);
					double t;
					if(tcell1 >= 0 && tnear+tcell1 <= texit){
						if(hit.hit(tnear+tcell1, this, matl)) {
			    			if(tcell2 >= 0) {
			    				hit.hit(tnear+tcell2, this, matl);
			    			}
					        *hit.getScratchpad<Vector>() = Vector(lx, ly, 0);
					        break;
			      		}
			    	} else if(tcell2 >= 0 && tnear+tcell2 <= texit){
			    		if(hit.hit(tnear+tcell2, this, matl)){
			        		*hit.getScratchpad<Vector>() = Vector(lx, ly, 0);
			        		break;
			      		}
			    	}
				}
			}
    	}
    	zenter = zexit;
    }
}

void Heightfield::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
    int lx = (int)((*hit.getScratchpad<Vector>()).x());
    int ly = (int)((*hit.getScratchpad<Vector>()).y());
    Point C = corner1 + Vector(lx, ly, 0)*cellsize;
    double dudx = 1/cellsize.x();
    double dvdy = 1/cellsize.y();
    double u = (hitpos.x()-C.x())*dudx;
    double v = (hitpos.y()-C.y())*dvdy;

	double Zu = data[lx+1][ly] - data[lx][ly];
	double Zv = data[lx][ly+1] - data[lx][ly];
	double Zuv = data[lx+1][ly+1] - data[lx+1][ly] - data[lx][ly+1] + data[lx][ly];
	
    normal =  Vector(-(dudx * Zu + dudx * v * Zuv), -(dvdy * Zv + dvdy * u * Zuv), 1);
    normal.normalize();
}
