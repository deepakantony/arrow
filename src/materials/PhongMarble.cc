
#include "PhongMarble.h"
#include "HitRecord.h"
#include "Light.h"
#include "Point.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include "PerlinNoise.h"
#include <iostream>

using namespace std;

PhongMarble::PhongMarble(const Color& color1, const Color& color2, const double scale, const int octaves,
				const double tscale, const double fscale, const double lacunarity, 
				const double gain, const double Kd, const double Ka, const Color& highlight,
				const double exponent)
:color1(color1), color2(color2), scale(scale), octaves(octaves), tscale(tscale), fscale(fscale),
lacunarity(lacunarity), gain(gain), PhongMaterial(color1, Kd,Ka,highlight,exponent)
{
}

void PhongMarble::shade(Color& result, const RenderContext& context, const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{	
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw, context, ray, hit);
	Vector T = uvw * scale * fscale;
	double value = cos(uvw.x() * scale + tscale * turbulenceAbs(octaves, Point(T), lacunarity, gain));
	value = value * 0.5 + 0.5;
	PhongMaterial::color = color1*(1-value) + color2*value;
	PhongMaterial::shade(result,context,ray,hit,atten,depth);
}
