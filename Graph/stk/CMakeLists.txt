# Collect STK source files
SET(STK_SOURCES
    "${OpenSolid}/Graph/stk/colour.cpp"
    "${OpenSolid}/Graph/stk/dumpGraphAction.cpp"
    "${OpenSolid}/Graph/stk/eventDispatcher.cpp"
    "${OpenSolid}/Graph/stk/eventListener.cpp"
    "${OpenSolid}/Graph/stk/Exception.cpp"
    "${OpenSolid}/Graph/stk/findGraphAction.cpp"
    "${OpenSolid}/Graph/stk/glLine.cpp"
    "${OpenSolid}/Graph/stk/glMaterial.cpp"
    "${OpenSolid}/Graph/stk/glStippleLine.cpp"
    "${OpenSolid}/Graph/stk/graphAction.cpp"
    "${OpenSolid}/Graph/stk/graphEdge.cpp"
    "${OpenSolid}/Graph/stk/graphNode.cpp"
    "${OpenSolid}/Graph/stk/graphUtil.cpp"
    "${OpenSolid}/Graph/stk/matrix_4x4.cpp"
    "${OpenSolid}/Graph/stk/namedObject.cpp"
    "${OpenSolid}/Graph/stk/NodeNotFound.cpp"
    "${OpenSolid}/Graph/stk/point.cpp"
    "${OpenSolid}/Graph/stk/propertiedObject.cpp"
    "${OpenSolid}/Graph/stk/property.cpp"
    "${OpenSolid}/Graph/stk/PropertyException.cpp"
    "${OpenSolid}/Graph/stk/transform.cpp"
    "${OpenSolid}/Graph/stk/threadCond.cpp"
    "${OpenSolid}/Graph/stk/threadedObject.cpp"
    "${OpenSolid}/Graph/stk/threadLock.cpp"
    "${OpenSolid}/Graph/stk/threadMutex.cpp"
    "${OpenSolid}/Graph/stk/uniqueObject.cpp"
    "${OpenSolid}/Graph/stk/vector3.cpp"
)

SET(GLOBAL_SOURCE_LIST   
    ${GLOBAL_SOURCE_LIST}
    ${STK_SOURCES}
    "${OpenSolid}/Graph/stk/CMakeLists.txt"
    PARENT_SCOPE
)
    
# Compile and link STK library
ADD_LIBRARY(OpenSolidSTK ${STK_SOURCES})
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
