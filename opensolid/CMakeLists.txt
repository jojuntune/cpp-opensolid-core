########## Set up required libraries ##########

    # Set up Python
    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

    # Set up Boost
    FIND_PACKAGE(Boost REQUIRED COMPONENTS python)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    # Add Boost library directory to link path so auto-linking works when using MSVC
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    
    # Set up Qt
    FIND_PACKAGE(Qt4 REQUIRED)
    SET(QT_USE_QTOPENGL ON)
    SET(QT_USE_QTXML ON)
    INCLUDE(${QT_USE_FILE})
    INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
    
    # Set up OpenGL
    FIND_PACKAGE(OpenGL REQUIRED)
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
    # Most POSIX systems have OpenGL headers in GL/ subdirectory
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR}/GL)
    # Mac OS X has OpenGL headers in Headers/ subdirectory of framework directory
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR}/Headers)
    
########## Set up build directory ##########

    # Place all executables, libraries in one directory
    IF (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
        SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    ELSE ()
        SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
        SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
    ENDIF ()

########## Set up testing ##########

    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    FIND_PACKAGE(PythonInterp REQUIRED)
    
    # Create macro for adding a CxxTest/CTest-based test
    MACRO(ADD_CXXTEST name source)
        GET_SOURCE_FILE_PROPERTY(FULL_PATH ${source} LOCATION)
        # Generate test source file
        ADD_CUSTOM_COMMAND(
            OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            DEPENDS
            "${FULL_PATH}"
            COMMAND
            "${PYTHON_EXECUTABLE}"
            ARGS
            "${OpenSolid_SOURCE_DIR}/external/cxxtest/bin/cxxtestgen"
            --error-printer
            -o "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            "${FULL_PATH}"
        )

        # Create test executable
        ADD_EXECUTABLE(${name} "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp")

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} "${EXECUTABLE_OUTPUT_PATH}/${name}")
    ENDMACRO(ADD_CXXTEST)
    
    # Add global source-checking test
    ADD_TEST(SourceChecks
        "${PYTHON_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/checker.py"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    
########## Build and install subprojects ##########

    ADD_SUBDIRECTORY(core)
    ADD_SUBDIRECTORY(python)

    INCLUDE_DIRECTORIES(graph graph/stk)
    ADD_SUBDIRECTORY(graph)
    ADD_SUBDIRECTORY(ui)

########## Top-level headers and files ##########

    SET(TOP_LEVEL_HEADERS core.hpp python.hpp)
    SET(TOP_LEVEL_FILES CMakeLists.txt checker.py)

    ADD_TO_GLOBAL_SOURCE_LIST(${TOP_LEVEL_HEADERS} ${TOP_LEVEL_FILES})

    INSTALL(FILES ${TOP_LEVEL_HEADERS} DESTINATION include/opensolid)
        
