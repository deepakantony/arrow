#ifndef METALMATERIAL_H_
#define METALMATERIAL_H_

#include "Material.h"
#include "utils/Color.h"

class MetalMaterial : public  Material {
 public:
  MetalMaterial(const Color& color, const float exponent);
  virtual ~MetalMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

 private:
  MetalMaterial(const MetalMaterial&);
  MetalMaterial& operator=(const MetalMaterial&);

  Color color, oneMinusColor;
  float exponent;
};

/*
#include "Material.h"
#include "Color.h"

class MetalMaterial : public  Material {
 public:
  MetalMaterial(const Color& color, const float exponent);
  virtual ~MetalMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

 private:
  MetalMaterial(const MetalMaterial&);
  MetalMaterial& operator=(const MetalMaterial&);

  Color color, oneMinusColor;
  float exponent;
};*/

#endif /*METALMATERIAL_H_*/
