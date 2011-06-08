
#ifndef Background_h
#define Background_h

class Color;
class Ray;
class RenderContext;

class Background {
 public:
  Background();
  virtual ~Background();

  virtual void preprocess();
  virtual void getBackgroundColor(Color& result, const RenderContext& context, const Ray& ray) = 0;

 private:
  Background(const Background&);
  Background& operator=(const Background&);
};

#endif

