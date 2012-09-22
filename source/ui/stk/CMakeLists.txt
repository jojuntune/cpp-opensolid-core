# Collect STK source files
set(
    STK_SOURCES
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

add_to_global_source_list(*)
    
# Compile and link STK library
add_library(opensolid_stk ${STK_SOURCES})
SET_TARGET_PROPERTIES(opensolid_stk PROPERTIES DEBUG_POSTFIX _debug)
TARGET_LINK_LIBRARIES(opensolid_stk ${QT_LIBRARIES})
