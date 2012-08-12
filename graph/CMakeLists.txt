# Build STK library
add_subdirectory(stk)
include_directories(stk)

# Collect graph library sources
set(GRAPH_SOURCES
    assemblyNode.cpp
    componentNode.cpp
    evaluateGraphAction.cpp
    fragmentNode.cpp
    graphAction.cpp
    graphScript.cpp
    graphNode.cpp
    graphParam.cpp
    graphParamList.cpp
    groupNode.cpp
    listGraphAction.cpp
    paramNode.cpp
    pointNode.cpp
    project.cpp
    renderGraphAction.cpp
)
add_to_global_source_list(${GRAPH_SOURCES} CMakeLists.txt)

# Build graph library
add_library(opensolid_graph ${GRAPH_SOURCES})
set_target_properties(opensolid_graph PROPERTIES DEBUG_POSTFIX "_debug")
target_link_libraries(opensolid_graph opensolid_stk opensolid_python ${OPENGL_LIBRARIES})
