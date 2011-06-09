include_directories(. ${ARROW_INCLUDE_DIRS})
link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(arrow ${ARROW_SRC}/main.cc)
target_link_libraries(arrow  
utils 
filters 
backgrounds 
materials   
cameras 
lights 
mapping 
objects 
sampler 
rtengine
parser)
