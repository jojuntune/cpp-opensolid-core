########## Define lists of source files ##########

    # Python directory files
    SET(PYTHON_FILES
        "${OpenSolid}/Python/bindTemplate.cpp"
        "${OpenSolid}/Python/CMakeLists.txt"
    )
    
    SET(PYTHON_HEADERS
        "${OpenSolid}/Python/config.hpp"
        "${OpenSolid}/Python/PythonEnvironment.hpp"
        "${OpenSolid}/Python/PythonModule.hpp"
        "${OpenSolid}/Python/PythonTests.hpp"
        "${OpenSolid}/Python/repr.hpp"
    )
    SET(PYTHON_MODULE_SOURCES
        "${OpenSolid}/Python/bindBounds.cpp"
        "${OpenSolid}/Python/bindComparison.cpp"
        "${OpenSolid}/Python/bindDatum.cpp"
        "${OpenSolid}/Python/bindDouble.cpp"
        "${OpenSolid}/Python/bindError.cpp"
        "${OpenSolid}/Python/bindFile.cpp"
        "${OpenSolid}/Python/bindFunction.cpp"
        "${OpenSolid}/Python/bindInterval.cpp"
        "${OpenSolid}/Python/bindMatrix.cpp"
        "${OpenSolid}/Python/bindMatrixConstructors.cpp"
        "${OpenSolid}/Python/bindObject.cpp"
        "${OpenSolid}/Python/bindSerialization.cpp"
        "${OpenSolid}/Python/bindSet.cpp"
        "${OpenSolid}/Python/bindSimplex.cpp"
        "${OpenSolid}/Python/PythonModule.cpp"
        "${OpenSolid}/Python/repr.cpp"
    )
    SET(PYTHON_ENVIRONMENT_SOURCES
        "${OpenSolid}/Python/PythonEnvironment.cpp"
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
    
    ADD_LIBRARY(OpenSolidPythonModule SHARED ${PYTHON_MODULE_SOURCES})
    SET_TARGET_PROPERTIES(OpenSolidPythonModule PROPERTIES PREFIX "" OUTPUT_NAME opensolid)
    IF(WIN32)
        SET_TARGET_PROPERTIES(OpenSolidPythonModule PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32)
    TARGET_LINK_LIBRARIES(OpenSolidPythonModule
        OpenSolidCore
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile OpenSolidPython library ##########
    
    ADD_LIBRARY(OpenSolidPython SHARED ${PYTHON_ENVIRONMENT_SOURCES})
    TARGET_LINK_LIBRARIES(OpenSolidPython
        OpenSolidCore
        OpenSolidPythonModule
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile tests ##########

    ADD_CXXTEST(PythonTests "${OpenSolid}/Python/PythonTests.hpp" OpenSolidPython OpenSolidCore)
    
########## Temporary fix - define 'override' as empty macro for GCC < 4.7 ##########
    
    IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
        SET_TARGET_PROPERTIES(
            opensolid
            OpenSolidPython
            PythonTests
            PROPERTIES
            COMPILE_FLAGS
            "-Doverride="
        )
    ENDIF()
    
########## Install headers ##########
    
    INSTALL(DIRECTORY ${OpenSolid}/Python
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenSolid"
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*Tests.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    INSTALL(TARGETS OpenSolidPython
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    )

    # Get site packages directory
    EXECUTE_PROCESS(
        COMMAND "${PYTHON_EXECUTABLE}"
        -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Install Python extension module
    INSTALL(TARGETS OpenSolidPythonModule DESTINATION ${PYTHON_SITE_PACKAGES})
