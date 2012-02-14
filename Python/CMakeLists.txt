########## Set up Python ##########

    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED COMPONENTS python)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    
    # Add Boost library directory to link path so auto-linking works when using MSVC
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

########## Define lists of source files ##########

    # Python directory files
    SET(PYTHON_FILES
        ${OpenSolid}/Python/bindTemplate.cpp
        ${OpenSolid}/Python/CMakeLists.txt
    )
    
    SET(PYTHON_HEADERS
        ${OpenSolid}/Python/config.hpp
        ${OpenSolid}/Python/PythonEnvironment.hpp
        ${OpenSolid}/Python/PythonModule.hpp
        ${OpenSolid}/Python/PythonTests.hpp
        ${OpenSolid}/Python/repr.hpp
    )
    SET(PYTHON_MODULE_SOURCES
        ${OpenSolid}/Python/bindBounds.cpp
        ${OpenSolid}/Python/bindComparison.cpp
        ${OpenSolid}/Python/bindDatum.cpp
        ${OpenSolid}/Python/bindDouble.cpp
        ${OpenSolid}/Python/bindError.cpp
        ${OpenSolid}/Python/bindFunction.cpp
        ${OpenSolid}/Python/bindHash.cpp
        ${OpenSolid}/Python/bindInterval.cpp
        ${OpenSolid}/Python/bindMatrix.cpp
        ${OpenSolid}/Python/bindMatrixConstructors.cpp
        ${OpenSolid}/Python/bindSerialization.cpp
        ${OpenSolid}/Python/bindSet.cpp
        ${OpenSolid}/Python/bindSimplex.cpp
        ${OpenSolid}/Python/PythonModule.cpp
        ${OpenSolid}/Python/repr.cpp
    )
    SET(PYTHON_ENVIRONMENT_SOURCES
        ${OpenSolid}/Python/PythonEnvironment.cpp
    )
    
    # Update global source list
    SET(GLOBAL_SOURCE_LIST ${GLOBAL_SOURCE_LIST}
        ${PYTHON_FILES}
        ${PYTHON_HEADERS}
        ${PYTHON_MODULE_SOURCES}
        ${PYTHON_ENVIRONMENT_SOURCES}
        PARENT_SCOPE
    )
    
########## Compile Python extension module ##########
    
    ADD_LIBRARY(opensolid SHARED ${PYTHON_MODULE_SOURCES})
    SET_TARGET_PROPERTIES(opensolid PROPERTIES PREFIX "")
    IF(WIN32)
        SET_TARGET_PROPERTIES(opensolid PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32)
    TARGET_LINK_LIBRARIES(opensolid OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
########## Compile OpenSolidPython library ##########
    
    ADD_LIBRARY(OpenSolidPython SHARED ${PYTHON_ENVIRONMENT_SOURCES})
    TARGET_LINK_LIBRARIES(OpenSolidPython
        OpenSolidCore
        opensolid
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile tests ##########

    ADD_CXXTEST(PythonTests ${OpenSolid}/Python/PythonTests.hpp OpenSolidPython OpenSolidCore)
    
########## Install headers ##########
    
    INSTALL(DIRECTORY ${OpenSolid}/Python
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/OpenSolid
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*Tests.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    INSTALL(TARGETS OpenSolidPython
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

    # Get site packages directory
    EXECUTE_PROCESS(
        COMMAND ${PYTHON_EXECUTABLE}
        -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Install Python extension module
    INSTALL(TARGETS opensolid DESTINATION ${PYTHON_SITE_PACKAGES})
