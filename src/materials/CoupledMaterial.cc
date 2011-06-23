
#include "CoupledMaterial.h"
#include "HitRecord.h"
#include "Light.h"
#include "Point.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include "mathutil.h"
using namespace std;

CoupledMaterial::CoupledMaterial(const Color& color, float Kd, float Ka, const Color& sHighlight, float exponent)
  :color(color), Kd(Kd), Ka(Ka), sHighlight(sHighlight), exponent(exponent)
{
}

CoupledMaterial::~CoupledMaterial()
{
}

void CoupledMaterial::shade(Color& result, const RenderContext& context,
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
	Color light = scene->getAmbient()*Ka;
	
	Color specularLight(0.0,0.0,0.0);
	
	double fr = pow(1-costheta,5);
	double ft = 1-fr;
	
	Light*const* begin = &lights[0];
	Light*const* end = &lights[0]+lights.size();
	while(begin != end){
		Color light_color;
		Vector light_direction;
		double dist = (*begin++)->getLight(light_color, light_direction, context, hitpos);
		double cosphi = Dot(normal, light_direction);
		if(cosphi > 0){
			HitRecord shadowhit(dist);
      		// Cast shadow rays...
			Ray shadowray(hitpos, light_direction);
			world->intersect(shadowhit, context, shadowray);
			if(!shadowhit.getPrimitive() || !shadowhit.getMaterial()->castShadows(context,shadowhit,shadowray)) {
				// No shadows...
				Vector h (light_direction - rayDir);
				h.normalize();
				
				double ndoth = Dot(normal, h);
				double specular = 0.0;
				if(ndoth > 0) {
					specular = pow(ndoth, exponent);
					specularLight += light_color*specular;
				}
				double fr1 = pow(1-cosphi, 5);
				double ft1 = 1 - fr1;
				
				light += light_color*ft*ft1*Kd;
				
				
			}
		}
	}
	result = light*color + specularLight*sHighlight;
	
		
	Color reflColor (0.0,0.0,0.0);
	
	//if(depth < scene->getMaxRayDepth()) {
		Vector reflectionDir = rayDir + 2 * costheta * normal;
		reflectionDir.normalize();
		Ray reflRay(hitpos, reflectionDir);
		scene->traceRay(reflColor, context, reflRay, atten, depth+1);
	//}
	
	
	result += color*reflColor*fr;
}

