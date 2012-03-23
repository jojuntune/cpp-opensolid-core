# Create STK library
ADD_SUBDIRECTORY(stk)

# Create tests
ADD_SUBDIRECTORY(tests)

# Collect graph library sources
SET(GRAPH_SOURCES
    "${OpenSolid}/Graph/assemblyNode.cpp"
    "${OpenSolid}/Graph/componentNode.cpp"
    "${OpenSolid}/Graph/evaluateGraphAction.cpp"
    "${OpenSolid}/Graph/fragmentNode.cpp"
    "${OpenSolid}/Graph/graphAction.cpp"
    "${OpenSolid}/Graph/graphScript.cpp"
    "${OpenSolid}/Graph/graphNode.cpp"
    "${OpenSolid}/Graph/graphParam.cpp"
    "${OpenSolid}/Graph/graphParamList.cpp"
    "${OpenSolid}/Graph/groupNode.cpp"
    "${OpenSolid}/Graph/listGraphAction.cpp"
    "${OpenSolid}/Graph/paramNode.cpp"
    "${OpenSolid}/Graph/pointNode.cpp"
    "${OpenSolid}/Graph/project.cpp"
    "${OpenSolid}/Graph/renderGraphAction.cpp"
)

SET(GLOBAL_SOURCE_LIST
    ${GLOBAL_SOURCE_LIST}
    ${GRAPH_SOURCES}
    "${OpenSolid}/Graph/CMakeLists.txt"
    PARENT_SCOPE
)

# Compile and link graph library
ADD_LIBRARY(OpenSolidGraph ${GRAPH_SOURCES})
TARGET_LINK_LIBRARIES(OpenSolidGraph OpenSolidSTK OpenSolidPython ${OPENGL_LIBRARIES})
