########## Define lists of source files ##########

    # Python directory files
    SET(PYTHON_FILES
        bindTemplate.cpp
        CMakeLists.txt
    )
    
    SET(PYTHON_HEADERS
        config.hpp
        PythonEnvironment.hpp
        PythonModule.hpp
        PythonTests.hpp
        repr.hpp
    )
    SET(PYTHON_MODULE_SOURCES
        bindBounds.cpp
        bindComparison.cpp
        bindDatum.cpp
        bindDouble.cpp
        bindError.cpp
        bindFunction.cpp
        bindInterval.cpp
        bindMatrix.cpp
        bindMatrixConstructors.cpp
        bindSet.cpp
        bindSimplex.cpp
        PythonModule.cpp
        repr.cpp
    )
    SET(PYTHON_ENVIRONMENT_SOURCES
        PythonEnvironment.cpp
    )
    
    ADD_TO_GLOBAL_SOURCE_LIST(
        ${PYTHON_FILES}
        ${PYTHON_HEADERS}
        ${PYTHON_MODULE_SOURCES}
        ${PYTHON_ENVIRONMENT_SOURCES}
    )
    
########## Compile Python extension module ##########
    
    ADD_LIBRARY(OpenSolidPythonModule SHARED ${PYTHON_MODULE_SOURCES})
    SET_TARGET_PROPERTIES(OpenSolidPythonModule PROPERTIES PREFIX "" OUTPUT_NAME opensolid)
    SET_TARGET_PROPERTIES(OpenSolidPythonModule PROPERTIES DEBUG_POSTFIX "d")
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
    SET_TARGET_PROPERTIES(OpenSolidPython PROPERTIES DEBUG_POSTFIX "d")
    TARGET_LINK_LIBRARIES(OpenSolidPython
        OpenSolidCore
        OpenSolidPythonModule
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile tests ##########

    ADD_CXXTEST(PythonTests PythonTests.hpp OpenSolidPython OpenSolidCore)
    
########## Temporary fix - define 'override' as empty macro for GCC < 4.7 ##########
    
    IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
        SET_TARGET_PROPERTIES(
            OpenSolidPythonModule
            OpenSolidPython
            PythonTests
            PROPERTIES
            COMPILE_FLAGS
            "-Doverride="
        )
    ENDIF()
    
########## Install headers ##########
    
    INSTALL(DIRECTORY .
        DESTINATION include/opensolid
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*Tests.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    INSTALL(TARGETS OpenSolidPython
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )

    # Get site packages directory
    EXECUTE_PROCESS(
        COMMAND "${PYTHON_EXECUTABLE}"
        -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Install Python extension module
    INSTALL(TARGETS OpenSolidPythonModule DESTINATION ${PYTHON_SITE_PACKAGES})
