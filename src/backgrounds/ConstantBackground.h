
#ifndef ConstantBackground_h
#define ConstantBackground_h

#include "Background.h"
#include "Color.h"

class ConstantBackground : public Background {
 public:
  ConstantBackground(const Color& color);
  virtual ~ConstantBackground();

  virtual void preprocess();
  virtual void getBackgroundColor(Color& result, const RenderContext& context, const Ray& ray);

 private:
  ConstantBackground(const ConstantBackground&);
  ConstantBackground& operator=(const ConstantBackground&);

  Color bgcolor;
};

#endif

