# Collect STK source files
SET(STK_SOURCES
    colour.cpp
    dumpGraphAction.cpp
    event.cpp
    eventDispatcher.cpp
    eventListener.cpp
    Exception.cpp
    findGraphAction.cpp
    glLine.cpp
    glMaterial.cpp
    glStippleLine.cpp
    graphAction.cpp
    graphEdge.cpp
    graphNode.cpp
    graphUtil.cpp
    matrix_4x4.cpp
    namedObject.cpp
    NodeNotFound.cpp
    point.cpp
    propertiedObject.cpp
    property.cpp
    PropertyException.cpp
    transform.cpp
    threadCond.cpp
    threadedObject.cpp
    threadLock.cpp
    threadMutex.cpp
    uniqueObject.cpp
    vector3.cpp
)

ADD_TO_GLOBAL_SOURCE_LIST(${STK_SOURCES} CMakeLists.txt)
    
# Compile and link STK library
ADD_LIBRARY(OpenSolidSTK ${STK_SOURCES})
SET_TARGET_PROPERTIES(OpenSolidSTK PROPERTIES DEBUG_POSTFIX "d")
TARGET_LINK_LIBRARIES(OpenSolidSTK ${QT_LIBRARIES})
   
# Temporary fix - define 'override' as empty macro for GCC < 4.7
IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
    SET_TARGET_PROPERTIES(
        OpenSolidSTK
        PROPERTIES
        COMPILE_FLAGS
        "-Doverride="
    )
ENDIF()
