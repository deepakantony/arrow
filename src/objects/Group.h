
#ifndef Group_h
#define Group_h

#include "Object.h"
#include <vector>

class Group : public Object {
 public:
  Group();
  virtual ~Group();

  void addObject(Object* object);
  virtual void preprocess();
  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;

 protected:
  std::vector<Object*> objects;

 private:
  Group(const Group&);
  Group& operator=(const Group&);
};

#endif

