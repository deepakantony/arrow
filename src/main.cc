#include "backgrounds/Background.h"
#include "cameras/Camera.h"
#include "backgrounds/ConstantBackground.h"
#include "utils/Color.h"
#include "objects/Group.h"
#include "utils/Image.h"
#include "materials/LambertianMaterial.h"
#include "lights/Light.h"
#include "materials/Material.h"
#include "objects/Object.h"
#include "cameras/PinholeCamera.h"
#include "objects/primitives/Plane.h"
#include "lights/PointLight.h"
#include "rtengine/Ray.h"
#include "rtengine/Scene.h"
#include "objects/primitives/Sphere.h"
#include "utils/Time.h"
#include "utils/Parser.h"
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
