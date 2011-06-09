add_library(objects
BoundingBox.cc
Group.cc
Instance.cc
Object.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})