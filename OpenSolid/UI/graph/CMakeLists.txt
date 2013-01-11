########## Build STK library ##########

    file(GLOB GRAPH_SOURCES *.cpp)
    add_library(opensolid_graph ${GRAPH_SOURCES})
    SET_TARGET_PROPERTIES(opensolid_graph PROPERTIES DEBUG_POSTFIX _debug)
    TARGET_LINK_LIBRARIES(opensolid_graph opensolid_stk opensolid_python ${OPENGL_LIBRARIES})

########## Add files to global source list ##########

    add_to_global_source_list(*)
