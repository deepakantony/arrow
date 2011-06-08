
#include "MetalMaterial.h"
#include "rtengine/HitRecord.h"
#include "lights/Light.h"
#include "utils/Point.h"
#include "objects/primitives/Primitive.h"
#include "rtengine/Ray.h"
#include "rtengine/RenderContext.h"
#include "rtengine/Scene.h"
#include "utils/Vector.h"
#include "utils/Math.h"
#include <float.h>
using namespace std;

MetalMaterial::MetalMaterial(const Color& color, const float exponent)
  :color(color), exponent(exponent)
{
	oneMinusColor = Color(1-color.r(), 1-color.g(), 1-color.b());
}

MetalMaterial::~MetalMaterial()
{
}

void MetalMaterial::shade(Color& result, const RenderContext& context,
                               const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{
	const Scene* scene = context.getScene();
	Vector rayDir = ray.direction();

	const vector<Light*>& lights = scene->getLights();
	Point hitpos = ray.origin()+rayDir*hit.minT();
	Vector normal;
	hit.getPrimitive()->normal(normal, context, hitpos, ray, hit);
	double costheta = Dot(normal, rayDir);
	if(costheta > 0)
		normal = -normal;
	else 
		costheta = -costheta;
		
	const Object* world = scene->getObject();
	Color light = scene->getAmbient();
	
	Color specularLight(0.0,0.0,0.0);
	
	Light*const* begin = &lights[0];
	Light*const* end = &lights[0]+lights.size();
	while(begin != end){
		Color light_color;
		Vector light_direction;
		double dist = (*begin++)->getLight(light_color, light_direction, context, hitpos);
		double cosphi = Dot(normal, light_direction);
		if(cosphi > 0){
      		// Cast shadow rays...
			HitRecord shadowhit(dist);
			if(castShadows(context, hit, ray)) {
				Ray shadowray(hitpos, light_direction);
				world->intersect(shadowhit, context, shadowray);
			}
			if(!shadowhit.getPrimitive()) {
				// No shadows...
				Vector h (light_direction - rayDir);
				h.normalize();
				
				double ndoth = Dot(normal, h);
				double specular = 0.0;
				if(ndoth > 0) {
					specular = pow(ndoth, exponent);
					specularLight += light_color*specular;
				}
				
			}
		}
	}
	result = specularLight*color;
	
	if(depth < scene->getMaxRayDepth()) {
		Color fresnel(color + oneMinusColor*pow(1-costheta, 5));
		
		Vector reflectionDir = rayDir + 2 * costheta * normal;
		reflectionDir.normalize();
		Color reflColor (0.0,0.0,0.0);
		
		Ray reflRay(hitpos, reflectionDir);
		scene->traceRay(reflColor, context, reflRay, atten*fresnel, depth+1);
    	result += reflColor*fresnel;
	}
	
}

