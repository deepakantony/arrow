
#include "ConstantBackground.h"
ConstantBackground::ConstantBackground(const Color& bgcolor)
  : bgcolor(bgcolor)
{
}

ConstantBackground::~ConstantBackground()
{
}

void ConstantBackground::preprocess()
{
}

void ConstantBackground::getBackgroundColor(Color& result, const RenderContext&,
                                            const Ray&)
{
  result=bgcolor;
}
