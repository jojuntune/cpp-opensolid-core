########## General setup ##########

    PROJECT(OpenSolid)
    # CMake 2.8.3 or later is required for CMAKE_CURRENT_LIST_DIR variable
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
    # Create convenience variable for referring to root OpenSolid directory
    SET(OpenSolid ${CMAKE_CURRENT_LIST_DIR})
    # Enable testing using CTest
    ENABLE_TESTING()

########## Set up compiler flags ##########

    # Set up compiler-specific flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Enable C++0x and add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wno-unused-variable")
        SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
        # Enable -fPIC on 64-bit systems where it is required
        IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Define nullptr as 0 on GCC versions earlier than 4.6
        EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF (GCC_VERSION VERSION_LESS 4.6)
            ADD_DEFINITIONS(-Dnullptr=0)
        ENDIF (GCC_VERSION VERSION_LESS 4.6)
    ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
        # Use -pthread compilation option to properly link to threading library
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    ELSEIF (WIN32)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        ADD_DEFINITIONS(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
        # Add /MP flag for parallel compilation within projects
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)
    
    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
    
    # Include parent directory to allow for #include <OpenSolid/...>, and External directory to
    # allow for #include <Eigen/...> etc.
    INCLUDE_DIRECTORIES(.. External)
    
########## Set up build directory ##########

    # Place all executables, libraries in one directory
    IF (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
        SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
    ELSE (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
        SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
    ENDIF (MSVC_IDE)

########## Create macro for .proto file compilation ##########

    MACRO(COMPILE_PROTO_FILES GENERATED_SOURCES)
        SET(${GENERATED_SOURCES})
        FOREACH(FULL_NAME ${ARGN})
            GET_FILENAME_COMPONENT(FILE_PATH ${FULL_NAME} PATH)
            GET_FILENAME_COMPONENT(BASE_NAME ${FULL_NAME} NAME_WE)
            ADD_CUSTOM_COMMAND(
                OUTPUT
                "${FILE_PATH}/${BASE_NAME}.pb.h"
                "${FILE_PATH}/${BASE_NAME}.pb.cc"
                DEPENDS
                protoc
                ${FULL_NAME}
                COMMAND
                protoc
                ARGS
                --proto_path=${FILE_PATH}
                --cpp_out=${FILE_PATH}
                ${FULL_NAME}
            )
            LIST(APPEND ${GENERATED_SOURCES} "${FILE_PATH}/${BASE_NAME}.pb.cc")
        ENDFOREACH(FULL_NAME)
    ENDMACRO(COMPILE_PROTO_FILES)

########## Set up testing ##########

    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    FIND_PACKAGE(PythonInterp REQUIRED)
    
    # Create macro for adding a CxxTest/CTest-based test
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
            ${OpenSolid}/External/cxxtest/cxxtestgen.py
            --error-printer
            -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
            ${source}
        )

        # Create test executable
        ADD_EXECUTABLE(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp)

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ENDMACRO(ADD_CXXTEST)
    
    # Add global source-checking test
    ADD_TEST(SourceChecks ${PYTHON_EXECUTABLE} ${OpenSolid}/checker.py ${OpenSolid})
    
########## Build subprojects ##########

    ADD_SUBDIRECTORY(External)
    ADD_SUBDIRECTORY(Core)
    ADD_SUBDIRECTORY(Python)
    ADD_SUBDIRECTORY(Documentation EXCLUDE_FROM_ALL)

########## Set up source groups for Visual Studio ##########

    # Automatically sort source files into groups based on directory structure
    INCLUDE(CreateSourceGroups.cmake)
    CREATE_SOURCE_GROUPS(${OpenSolid} ${GLOBAL_SOURCE_LIST})

    # Include all directories included by subprojects to allow code completion to work properly
    # within ALL_SOURCES target
    GET_DIRECTORY_PROPERTY(CORE_INCLUDES DIRECTORY Core INCLUDE_DIRECTORIES)
    GET_DIRECTORY_PROPERTY(PYTHON_INCLUDES DIRECTORY Python INCLUDE_DIRECTORIES)
    INCLUDE_DIRECTORIES(${CORE_INCLUDES})
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDES})
    
    # Dummy library that is never built but provides a Visual Studio target that includes
    # a complete source tree
    ADD_LIBRARY(ALL_SOURCES EXCLUDE_FROM_ALL ${GLOBAL_SOURCE_LIST})
        
