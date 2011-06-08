

#ifndef DIELECTRICMATERIAL_H_
#define DIELECTRICMATERIAL_H_

#include "Material.h"
#include "utils/Color.h"

class DielectricMaterial : public Material {
 public:
  DielectricMaterial(const float eta, const float exponent, const Color& attenuation);
  virtual ~DielectricMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

 protected:
  DielectricMaterial(const DielectricMaterial&);
  DielectricMaterial& operator=(const DielectricMaterial&);
  
  inline Color beersAttenuation(double t) const {
  	return Color(exp(t*logOfAttenuation.r()),exp(t*logOfAttenuation.g()),exp(t*logOfAttenuation.b()));
  }

  float eta;
  float exponent;
  float R0;
  float etaReciprocal;
  Color logOfAttenuation;
};

#endif /*DIELECTRICMATERIAL_H_*/
