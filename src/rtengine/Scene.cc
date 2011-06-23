
#include "Scene.h"
#include "Background.h"
#include "Camera.h"
#include "HitRecord.h"
#include "Image.h"
#include "mathutil.h"
#include "Light.h"
#include "Material.h"
#include "Object.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Sampler.h"
#include "Filter.h"
#include <float.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

Scene::Scene()
{
  object = 0;
  background = 0;
  camera = 0;
  ambient = Color(0, 0, 0);
  image = 0;
  minAttenuation = 0;
}

Scene::~Scene()
{
  delete object;
  delete background;
  delete camera;
  delete image;
	delete sampler;
	delete filter;
  for(int i=0;i<static_cast<int>(lights.size());i++){
    Light* light = lights[i];
    delete light;
  }
}

void Scene::preprocess()
{
  cout << "background..." << flush;
  background->preprocess();
  cout << "light..." << flush;
  for(int i=0;i<static_cast<int>(lights.size());i++){
    Light* light = lights[i];
    light->preprocess();
  }
  double aspect_ratio = image->aspect_ratio();
  cout << "camera..." << flush;
  camera->preprocess(aspect_ratio);
  cout << "object..." << flush;
  object->preprocess();
  cout << "sampler..." << flush;
  samplesPerPixel = sampler->getSamplesPerPixel();
}

void Scene::render()
{
  if(!object || !background || !camera || !image){
    cerr << "Incomplete scene, cannot render!\n";
    exit(1);
  }
  int xres = image->getXresolution();
  int yres = image->getYresolution();
  RenderContext context(this);
  double dx = 2./xres;
  int sqrtSpp = (int)round(sqrt(samplesPerPixel));
  double xmin = -1. + dx/2.0;
  double dy = 2./yres;
  double ymin = -1. + dy/2.0;
  Color atten(1,1,1);
  int support = filter->getSupport();
	
  Color *imageColor = new Color[xres*yres];
  double *totalWeights = new double[xres*yres];
  for(int ctr = 0; ctr < xres*yres; ctr++)
    totalWeights[ctr] = 0.0;

  for(int i=0;i<yres;i++){
    for(int j=0;j<xres;j++){
      cout << "Pixel: " << i*yres+j+1 << "\r" << flush;
      Color result(0.0,0.0,0.0);
      double totalWeight = 0.0;
      for(int k = 0; k < samplesPerPixel; k++) {
	Point sample = sampler->getNextSample();
	double samplex = sample.x(), sampley = sample.y();
	double x = xmin + j*dx + dx*samplex;
	double y = ymin + i*dy + dy*sampley;
	Ray ray;
	camera->makeRay(ray, context, x, y);
	HitRecord hit(DBL_MAX);
	object->intersect(hit, context, ray);
	Color sampleColor;
	if(hit.getPrimitive()){
	  // Ray hit something...
	  const Material* matl = hit.getMaterial();
	  matl->shade(sampleColor, context, ray, hit, atten, 0);
	} else {
	  background->getBackgroundColor(sampleColor, context, ray);
	}
	double colorWeight = filter->evaluate(samplex, sampley);
	result += sampleColor*colorWeight;
	totalWeight += colorWeight;
			
	if(support > 1) {
	  int range = support-1;
	  for(int a = -range; a <= range; a++) {
	    int Y = i+a;
	    if(Y < 0 || Y > yres-1) continue;
					
	    for(int b = -range; b <= range; b++) {
						
	      int X = j+b;
	      //if(X==j && Y==i) continue;
	      if(X < 0 || X > xres-1) continue;
						
	      double pixelCenterX = xmin + X*dx;
	      double pixelCenterY = ymin + Y*dy;
						
	      // get the distance between this pixel and the sample
	      double x_X = Abs(x-pixelCenterX)/dx;
	      double y_Y = Abs(y-pixelCenterY)/dy;
	      if(range>1) {
		x_X = x_X/range;
		y_Y = y_Y/range;
	      }
	      else if(range == 0) {
		x_X *= 2.0;
		y_Y *= 2.0;
	      }
	      x_X = Clamp(x_X, 0.0, 1.0);
	      y_Y = Clamp(y_Y, 0.0, 1.0);
						
	      double colorWeight2 = filter->evaluate(x_X, y_Y);
	      imageColor[X+Y*xres] += sampleColor*colorWeight2;
	      totalWeights[X+Y*xres] += colorWeight2;
	    }
	  }					
	}
			
	imageColor[j+i*xres] += sampleColor*colorWeight;
	totalWeights[j+i*xres] += colorWeight;
      }
    }
  }
  cout << endl;
  for(int i = 0; i < yres; i++)
    for(int j = 0; j < xres; j++)
      image->set(j, i, imageColor[j+i*xres]/totalWeights[j+i*xres]);
			
}

double Scene::traceRay(Color& result, const RenderContext& context, const Ray& ray, const Color& atten, int depth) const
{
  if(depth >= maxRayDepth || atten.maxComponent() < minAttenuation){
    result = Color(0, 0, 0);
    return 0;
  } else {
    HitRecord hit(DBL_MAX);
    object->intersect(hit, context, ray);
    if(hit.getPrimitive()){
      // Ray hit something...
      const Material* matl = hit.getMaterial();
      matl->shade(result, context, ray, hit, atten, depth);
      return hit.minT();
    } else {
      background->getBackgroundColor(result, context, ray);
      return DBL_MAX;
    }
  }
}

double Scene::traceRay(Color& result, const RenderContext& context, const Object* obj, const Ray& ray, const Color& atten, int depth) const
{
  if(depth >= maxRayDepth || atten.maxComponent() < minAttenuation){
    result = Color(0, 0, 0);
    return 0;
  } else {
    HitRecord hit(DBL_MAX);
    obj->intersect(hit, context, ray);
    if(hit.getPrimitive()){
      // Ray hit something...
      const Material* matl = hit.getMaterial();
      matl->shade(result, context, ray, hit, atten, depth);
      return hit.minT();
    } else {
      background->getBackgroundColor(result, context, ray);
      return DBL_MAX;
    }
  }
}
