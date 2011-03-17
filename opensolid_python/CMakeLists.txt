ADD_LIBRARY(
    opensolid_python
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
SET_TARGET_PROPERTIES(opensolid_python PROPERTIES PREFIX "")
IF(WIN32)
    SET_TARGET_PROPERTIES(opensolid_python PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(opensolid_python opensolid ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
INSTALL(
    TARGETS opensolid_python
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
