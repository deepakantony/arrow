add_library(materials
CheckerMaterial.cc
CoupledMaterial.cc
DielectricMaterial.cc
InvisibleMaterial.cc
LambertianMaterial.cc
Material.cc
MetalMaterial.cc
OrenNayarMaterial.cc
PhongDielectricImage.cc
PhongImageMaterial.cc
PhongMarble.cc
PhongMaterial.cc
TestFunctionMaterial.cc
TileMaterial.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})