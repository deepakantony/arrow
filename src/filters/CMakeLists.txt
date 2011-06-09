add_library(filters  
BoxFilter.cc
Filter.cc
GaussianFilter.cc
MitchellFilter.cc
TriangleFilter.cc
WindowedSincFilter.cc)
add_dependencies(filters utils)
include_directories(. ${ARROW_INCLUDE_DIRS})