
#include "Image.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

static void error(const std::string& filename, const std::string& errtext)
{
  cerr << "Error reading image: " << filename << ": " << errtext << '\n';
  exit(1);
}

Image::Image(const std::string& filename)
{
  cerr << "Reading " << filename << "...";
  ifstream in(filename.c_str(), ios::in | ios::binary);
  if(!in)
    error(filename, "Error opening file");
  if(in.get() != 'P' || !in)
    error(filename, "Error reading magic number (1st digit)");
  if(in.get() != '6' || !in)
    error(filename, "Error reading magic number (2nd digit)");
  int maxValue;
  in >> xres >> yres >> maxValue;
  in.get();
  cerr << " " << xres << "x" << yres << "...";
  if(!in)
    error(filename, "Error reading metadaa");
  data = new Pixel*[yres];
  Pixel* p = new Pixel[xres*yres];
  for(int i=0;i<yres;i++)
    data[i] = p + i*xres;
  for(int i=yres-1;i>=0;i--)
    in.read(reinterpret_cast<char*>(data[i]), sizeof(Pixel)*xres);
  if(!in)
    error(filename, "Error reading pixels");
	
  cerr << " done\n";
}

Image::Image(int xres, int yres)
  : xres(xres), yres(yres)
{
  data = new Pixel*[yres];
  Pixel* p = new Pixel[xres*yres];
  for(int i=0;i<yres;i++)
    data[i] = p + i*xres;
}

Image::~Image()
{
  delete[] data[0];
  delete[] data;
}

void Image::write(const std::string& filename) const
{
  std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
  out << "P6 " << xres << " " << yres << " 255\n";
  for(int i=yres-1;i>=0;i--)
    out.write(reinterpret_cast<char*>(data[i]), sizeof(Pixel)*xres);
}
