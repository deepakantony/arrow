add_library(cameras Camera.cc PinholeCamera.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})