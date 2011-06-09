add_library(utils
Color.cc
Image.cc
PerlinNoise.cc
Point.cc
Time.cc
Vector.cc
Matrix.cpp)
add_library(parser parser.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})