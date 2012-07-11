# Create STK library
ADD_SUBDIRECTORY(stk)

# Create tests
ADD_SUBDIRECTORY(tests)

# Collect graph library sources
SET(GRAPH_SOURCES
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

ADD_TO_GLOBAL_SOURCE_LIST(${GRAPH_SOURCES} CMakeLists.txt)

# Compile and link graph library
ADD_LIBRARY(OpenSolidGraph ${GRAPH_SOURCES})
SET_TARGET_PROPERTIES(OpenSolidGraph PROPERTIES DEBUG_POSTFIX "d")
TARGET_LINK_LIBRARIES(OpenSolidGraph OpenSolidSTK OpenSolidPython ${OPENGL_LIBRARIES})
   
# Temporary fix - define 'override' as empty macro for GCC < 4.7    
IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
    SET_TARGET_PROPERTIES(
        OpenSolidGraph
        PROPERTIES
        COMPILE_FLAGS
        "-Doverride="
    )
ENDIF()
