#include "Background.h"
#include "Camera.h"
#include "ConstantBackground.h"
#include "Color.h"
#include "Group.h"
#include "Image.h"
#include "LambertianMaterial.h"
#include "Light.h"
#include "Material.h"
#include "Object.h"
#include "PinholeCamera.h"
#include "Plane.h"
#include "PointLight.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Time.h"
#include "Parser.h"
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  double t1 = Time::currentSeconds();

  if ( argc < 2 ) {
    cerr << "Usage: specter scene" << endl;
    return 1;
  }
  
  ifstream scene_file( argv[ 1 ] );
  //ifstream scene_file("/home/beast/Desktop/daray/scenes/prog04/prog04.scn");
  if ( !scene_file.good() ) {
    cerr << "Unable to read scene file: " << argv[ 1 ] << endl;
    return 1;
  }
  Parser reader( scene_file );
  string filename = "image.ppm";
  Scene *scene = reader.parseScene( filename );

  scene->preprocess();

  double t2 = Time::currentSeconds();
  scene->render();

  double t3 = Time::currentSeconds();
  scene->getImage()->write(filename);

  double t4 = Time::currentSeconds();
  cerr << "Setup/load time:\t" << setprecision(3) << t2-t1 << " seconds\n";
  cerr << "Render time:\t\t" << setprecision(3) << t3-t2 << " seconds\n";
  cerr << "Post-process time:\t" << setprecision(3) << t4-t3 << " seconds\n";
  return 0;
}
