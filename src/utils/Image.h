
#ifndef Image_h
#define Image_h

#include "Color.h"
#include "mathutil.h"
#include <string>
#include <iostream>

using namespace std;

struct Pixel {
  unsigned char r, g, b;
};

class Image {
 public:
  Image(const std::string& name);
  Image(int xres, int yres);
  ~Image();
  void set(int x, int y, const Color& c) {
    Pixel p;
    p.r = c.r() < 0.f? 0: c.r() >= 1.f? 255 : (int)(c.r() * 255.f);
    p.g = c.g() < 0.f? 0: c.g() >= 1.f? 255 : (int)(c.g() * 255.f);
    p.b = c.b() < 0.f? 0: c.b() >= 1.f? 255 : (int)(c.b() * 255.f);
    data[y][x] = p;
  }
	Color get(int x, int y) {
		return Color((double)data[y][x].r/255.0, (double)data[y][x].g/255.0, (double)data[y][x].b/255.0);
	}
  void write(const std::string& filename) const;
  double aspect_ratio() const {
    return double(xres)/double(yres);
  }
  int getXresolution() {
    return xres;
  }
  int getYresolution() {
    return yres;
  }
  Color interpolate(float x, float y) const {
    x *= xres; y *= yres;
    int ix = Floor(x)%xres;
    if(ix<0)
      ix += xres;
    int ix1 = (ix+1)%xres;
    int iy = Floor(y)%yres;
    if(iy<0)
      iy += yres;
    int iy1 = (iy+1)%yres;
    float fx = x-ix;
    float fy = y-iy;

    Color c00 = Color(data[iy][ix].r,   data[iy][ix].g,   data[iy][ix].b);
    Color c01 = Color(data[iy][ix1].r,  data[iy][ix1].g,  data[iy][ix1].b);
    Color c10 = Color(data[iy1][ix].r,  data[iy1][ix].g,  data[iy1][ix].b);
    Color c11 = Color(data[iy1][ix1].r, data[iy1][ix1].g, data[iy1][ix1].b);
    Color c = c00*(1-fx)*(1-fy) + c01*fx*(1-fy) + c10*(1-fx)*fy + c11*fx*fy;
    return c*(1./255);
  }
 protected:
  Pixel** data;
  int xres, yres;
  Image(const Image&);
  Image& operator=(const Image&);
};

#endif
