ADD_LIBRARY(
    OpenSolidPython
    SHARED
    bindError.cpp
    bindInterval.cpp
    bindTolerance.cpp
    bindEigen.cpp
    bindSpecificMatrixSizes.cpp
    bindFunction.cpp
    bindAll.cpp
    check.cpp
)

# Configure library name (opensolid_python.so on UNIX, opensolid_python.pyd on Windows)
SET_TARGET_PROPERTIES(OpenSolidPython PROPERTIES PREFIX "")
IF(WIN32)
    SET_TARGET_PROPERTIES(OpenSolidPython PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(OpenSolidPython OpenSolid ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
INSTALL(
    TARGETS OpenSolidPython
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
