cmake_minimum_required (VERSION 2.6)
project (ARROW)

SET(LIBRARY_OUTPUT_PATH ${ARROW_BINARY_DIR}/lib)
SET(ARROW_SRC ${ARROW_SOURCE_DIR})
SET(ARROW_INCLUDE_DIRS 
${ARROW_SRC}/backgrounds 
${ARROW_SRC}/cameras 
${ARROW_SRC}/utils 
${ARROW_SRC}/objects 
${ARROW_SRC}/objects/primitives 
${ARROW_SRC}/materials 
${ARROW_SRC}/lights 
${ARROW_SRC}/rtengine 
${ARROW_SRC}/sampler 
${ARROW_SRC}/filters
${ARROW_SRC}/mapping)


add_library(rtengine
rtengine/Scene.cc
utils/Parser.cc
objects/BoundingBox.cc
objects/Group.cc
objects/Instance.cc
objects/Object.cc
objects/primitives/Box.cc
objects/primitives/Cone.cc
objects/primitives/Cylinder.cc
objects/primitives/Heightfield.cc
objects/primitives/Plane.cc
objects/primitives/Primitive.cc
objects/primitives/Rectangle.cc
objects/primitives/Sphere.cc
objects/primitives/SpherePolar.cc
objects/primitives/Torus.cc
objects/primitives/disk.cc
objects/primitives/ring.cc
objects/primitives/triangle.cc
cameras/Camera.cc
cameras/PinholeCamera.cc
lights/Light.cc 
lights/PointLight.cc
materials/CheckerMaterial.cc
materials/CoupledMaterial.cc
materials/DielectricMaterial.cc
materials/InvisibleMaterial.cc
materials/LambertianMaterial.cc
materials/Material.cc
materials/MetalMaterial.cc
materials/OrenNayarMaterial.cc
materials/PhongDielectricImage.cc
materials/PhongImageMaterial.cc
materials/PhongMarble.cc
materials/PhongMaterial.cc
materials/TestFunctionMaterial.cc
materials/TileMaterial.cc
sampler/HammersleySampler.cc
sampler/JitteredSampler.cc
sampler/MultiJitteredSampler.cc
sampler/NRooksSampler.cc
sampler/Sampler.cc
sampler/TestFunctionMaterial.cc
sampler/UniformSampler.cc
)
target_link_libraries(rtengine utils filters mapping backgrounds)
include_directories(. ${ARROW_INCLUDE_DIRS})

add_subdirectory(cameras)
add_subdirectory(lights)
add_subdirectory(mapping)
add_subdirectory(objects)
add_subdirectory(sampler)
#add_subdirectory(world)
add_subdirectory(backgrounds)
add_subdirectory(filters)
add_subdirectory(materials)
add_subdirectory(rtengine)
add_subdirectory(utils)

link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(arrow ${ARROW_SRC}/main.cc)
target_link_libraries(arrow  
utils 
backgrounds
filters
mapping
rtengine
)

