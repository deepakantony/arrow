cmake_minimum_required (VERSION 2.6)
project (ARROW)

SET(LIBRARY_OUTPUT_PATH ${ARROW_BINARY_DIR}/lib)
SET(ARROW_SRC ${ARROW_SOURCE_DIR}/src)
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

subdirs(src bin)
