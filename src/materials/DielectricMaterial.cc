
#include "DielectricMaterial.h"
#include "HitRecord.h"
#include "Light.h"
#include "Point.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include "Math.h"
#include <float.h>
#include <math.h>

using namespace std;

DielectricMaterial::DielectricMaterial(const float eta, const float exponent, const Color& attenuation)
  :eta(eta), exponent(exponent)
{
	this->logOfAttenuation = Color(log(attenuation.r()), log(attenuation.g()), log(attenuation.b()));
	R0 = (eta-1)*(eta-1)/((eta+1)*(eta+1));
	etaReciprocal = 1/eta;
}

DielectricMaterial::DielectricMaterial(const DielectricMaterial& matl)
{
	this->eta = matl.eta;
	this->exponent = matl.exponent;
	this->R0 = matl.R0;
	this->etaReciprocal = matl.etaReciprocal;
	this->logOfAttenuation = matl.logOfAttenuation;
}

DielectricMaterial::~DielectricMaterial()
{
}

void DielectricMaterial::shade(Color& result, const RenderContext& context,
                               const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{
	const Scene* scene = context.getScene();
	Vector rayDir = ray.direction();

	const vector<Light*>& lights = scene->getLights();
	Point hitpos = ray.origin()+rayDir*hit.minT();
	Vector normal;
	hit.getPrimitive()->normal(normal, context, hitpos, ray, hit);
	double costheta = Dot(normal, rayDir);
	float etaTemp;
	Vector unflippedNormal(normal);
	if(costheta > 0) {
		normal = -normal;
		etaTemp = etaReciprocal;
	}
	else { 
		costheta = -costheta;
		etaTemp = eta;
	}
	
	const Object* world = scene->getObject();
	
	Color specularLight(0.0,0.0,0.0);
	
	Light*const* begin = &lights[0];
	Light*const* end = &lights[0]+lights.size();
	//begin++;
	while(begin != end){
		Color light_color;
		Vector light_direction;
		double dist = (*begin++)->getLight(light_color, light_direction, context, hitpos);
		double cosphi = Dot(normal, light_direction);
  		// Cast shadow rays...
		HitRecord shadowhit(dist);

		Ray shadowray(hitpos, light_direction);
		world->intersect(shadowhit, context, shadowray);
		if(!shadowhit.getPrimitive() || !shadowhit.getMaterial()->castShadows(context,shadowhit,shadowray)) {
			// No shadows...
			Vector h ;
			
			if(cosphi > 0) 
				h = light_direction - rayDir;
			else 
				h = light_direction + rayDir;
				
			h.normalize();
			
			double ndoth = Dot(unflippedNormal, h);
			double specular = 0.0;
			if(ndoth > 0) {
				specular = pow(ndoth, exponent);
				specularLight += light_color*specular;
			}
		}
	}
	result = specularLight;
	
	if(depth < scene->getMaxRayDepth()) {
		Vector reflectionDir = rayDir + 2 * costheta * normal;
		reflectionDir.normalize();
		Color reflColor (0.0,0.0,0.0);
		Ray reflRay(hitpos, reflectionDir);

		double costheta2sqr = 1 + (costheta*costheta-1)/(etaTemp*etaTemp);
		if(costheta2sqr < 0) {
			double ndotrefl = Dot(normal, reflectionDir);
			// Total internal refraction
			double t = scene->traceRay(reflColor, context, reflRay, atten, depth+1);
			
			if(ndotrefl >= 0)
				result += reflColor*beersAttenuation(t);
			else
				result += reflColor;
		}
		else {
			double ndotrefl = Dot(normal, reflectionDir);
			double costheta2 = sqrt(costheta2sqr);
			double cosm = min(costheta, costheta2);
			double fresnel = R0 + (1-R0)*pow(1-cosm, 5);
			
			double t;
			t = scene->traceRay(reflColor, context, reflRay, atten*fresnel, depth+1);
			
			if( ndotrefl >= 0 )
				result += reflColor*fresnel*beersAttenuation(t);
			else 
				result += reflColor*fresnel;

			double fresnelTransmitter = 1.0 - fresnel;
			
			Vector transparencyRayDir((rayDir/etaTemp) + ((costheta/etaTemp) - costheta2)*normal);
			transparencyRayDir.normalize();
			
			Ray transparencyRay(hitpos, transparencyRayDir);
			Color transpColor(0.0,0.0,0.0);
			
			t = scene->traceRay(transpColor, context, transparencyRay, atten*fresnelTransmitter, depth+1);
			double ndottransp = Dot(normal, transparencyRayDir);
			
			if(ndottransp >= 0)
				result += transpColor*fresnelTransmitter*beersAttenuation(t);
			else
				result += transpColor*fresnelTransmitter;
		}
	}
}
