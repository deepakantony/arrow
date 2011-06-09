
#ifndef TestFunctionMaterial_h
#define TestFunctionMaterial_h

#include "Material.h"
#include "Color.h"

class TestFunctionMaterial : public Material {
 public:
  TestFunctionMaterial();
  virtual ~TestFunctionMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

 private:
  TestFunctionMaterial(const TestFunctionMaterial&);
  TestFunctionMaterial& operator=(const TestFunctionMaterial&);
};

#endif
