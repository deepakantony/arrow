
#include "TestFunctionMaterial.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
using namespace std;

TestFunctionMaterial::TestFunctionMaterial()
{
}

TestFunctionMaterial::~TestFunctionMaterial()
{
}

void TestFunctionMaterial::shade(Color& result, const RenderContext& context,
                               const Ray& ray, const HitRecord& hit, const Color&, int) const
{
  Point hitpos = ray.origin()+ray.direction()*hit.minT();
  double rs = hitpos.x() * hitpos.x() + hitpos.y() * hitpos.y();
  double grey = cos( 500.0 * 3.141592653589793 * rs ) * 0.5 + 0.5;
  result = Color( grey, grey, grey );
}