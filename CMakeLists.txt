########## General setup ##########

    PROJECT(OpenSolid)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
    ENABLE_TESTING()

    # GCC-specific compiler flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-variable -fno-strict-aliasing")
        # Enable -fPIC on 64-bit systems where it is required
        IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)

    # FreeBSD-specific compiler flags
    IF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
        # Use -pthread compilation option to properly link to threading library
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    
    # Windows-specific compiler flags
    IF (WIN32)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        ADD_DEFINITIONS(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS)
    ENDIF (WIN32)

    # Collect compiled binaries in single directory
    IF (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${OpenSolid_BINARY_DIR})
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolid_BINARY_DIR})
    ELSE (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${OpenSolid_BINARY_DIR}/bin)
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolid_BINARY_DIR}/bin)
    ENDIF (MSVC_IDE)

    # Initialize local include paths
    INCLUDE_DIRECTORIES(BEFORE ${OpenSolid_SOURCE_DIR} external)

########## Set up Python ##########

    FIND_PACKAGE(PythonInterp REQUIRED)
    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED COMPONENTS python)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    
    # Add Boost library directory to link path so auto-linking works when using MSVC
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

########## Set up OpenGL ##########

    FIND_PACKAGE(OpenGL REQUIRED)
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
    
    # Most POSIX systems have OpenGL headers in GL/ subdirectory
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR}/GL)
    
    # Mac OS X has OpenGL headers in Headers/ subdirectory of framework directory
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR}/Headers)

########## Set up Qt ##########

    FIND_PACKAGE(Qt4 REQUIRED)
    SET(QT_USE_QTOPENGL ON)
    SET(QT_USE_QTXML ON)
    INCLUDE(${QT_USE_FILE})
    INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
    ADD_DEFINITIONS(${QT_DEFINITIONS})

########## Set up CxxTest ##########

    MACRO(ADD_CXXTEST name source)
        # Generate test source file
        ADD_CUSTOM_COMMAND(
            OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
            DEPENDS
            ${source}
            COMMAND
            ${PYTHON_EXECUTABLE}
            ARGS
            ${OpenSolid_SOURCE_DIR}/external/cxxtest/cxxtestgen.py
            --error-printer
            -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/${source}
        )

        # Create test executable
        ADD_EXECUTABLE(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp)

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ENDMACRO(ADD_CXXTEST)
    
########## Compile and install ##########
    
    # Install Eigen headers
    INSTALL(
        DIRECTORY external/Eigen
        DESTINATION include
        PATTERN ".svn" EXCLUDE
        PATTERN "CMakeLists.txt" EXCLUDE
    )

    # Install OpenSolid headers
    INSTALL(
        DIRECTORY opensolid
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN ".svn" EXCLUDE
        PATTERN "*.tests.hpp" EXCLUDE
    )

    # Compile and install libraries and tests in subdirectories
    ADD_SUBDIRECTORY(opensolid)
    ADD_SUBDIRECTORY(opensolid_python)
    ADD_SUBDIRECTORY(opensolid_scripting)

########## Generate documentation ##########

    ADD_SUBDIRECTORY(doc EXCLUDE_FROM_ALL)
