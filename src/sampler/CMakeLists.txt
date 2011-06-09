add_library(sampler 
HammersleySampler.cc
JitteredSampler.cc
MultiJitteredSampler.cc
NRooksSampler.cc
Sampler.cc
TestFunctionMaterial.cc
UniformSampler.cc)
include_directories(. ${ARROW_INCLUDE_DIRS})