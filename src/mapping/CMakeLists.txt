add_library(mapping Mapping.cc PlanarMapping.cc SphericalMapping.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})