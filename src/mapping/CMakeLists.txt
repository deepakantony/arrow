add_library(mapping  Mapping.cc PlanarMapping.cc SphericalMapping.cc)
add_dependencies(mapping utils)
include_directories(. ${ARROW_INCLUDE_DIRS})