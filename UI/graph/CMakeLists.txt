file(GLOB GRAPH_SOURCES *.cpp)
add_library(opensolid_graph ${GRAPH_SOURCES})
SET_TARGET_PROPERTIES(opensolid_graph PROPERTIES DEBUG_POSTFIX _debug)
TARGET_LINK_LIBRARIES(opensolid_graph opensolid_stk opensolid_python ${OPENGL_LIBRARIES})
