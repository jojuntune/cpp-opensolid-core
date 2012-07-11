########## General setup ##########
    
    # Enable testing using CTest
    ENABLE_TESTING()

########## Set up compiler flags ##########

    # Set up compiler-specific flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Enable C++0x and pthread and add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread -Wall -Wno-unused-variable")
        ADD_DEFINITIONS(-DHAVE_PTHREAD)
        SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
        # Enable -fPIC on 64-bit systems where it is required
        IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
            SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
        ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Define nullptr as 0 on GCC versions earlier than 4.6
        EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF (GCC_VERSION VERSION_LESS 4.6)
            ADD_DEFINITIONS(-Dnullptr=0)
        ENDIF ()
    ELSEIF (MSVC)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        ADD_DEFINITIONS(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
        # Add /MP flag for parallel compilation within projects
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        # Disable incremental linking (seems to cause erros in debug builds)
        SET(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL:NO")
        SET(CMAKE_SHARED_LINKER_FLAGS "/INCREMENTAL:NO")
        SET(CMAKE_MODULE_LINKER_FLAGS "/INCREMENTAL:NO")
    ENDIF ()
    
    # Include parent directory to allow for #include <opensolid/...>, and External directory to
    # allow for #include <Eigen/...> etc.
    INCLUDE_DIRECTORIES(.. ../External)

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
    ELSE (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
        SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
    ENDIF (MSVC_IDE)

########## Set up testing ##########

    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    FIND_PACKAGE(PythonInterp REQUIRED)
    
    # Create macro for adding a CxxTest/CTest-based test
    MACRO(ADD_CXXTEST name source)
        # Generate test source file
        ADD_CUSTOM_COMMAND(
            OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            DEPENDS
            "${source}"
            COMMAND
            "${PYTHON_EXECUTABLE}"
            ARGS
            "${OpenSolid_SOURCE_DIR}/External/cxxtest/cxxtestgen.py"
            --error-printer
            -o "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            "${source}"
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

    ADD_SUBDIRECTORY(Core)
    ADD_SUBDIRECTORY(Python)

    INCLUDE_DIRECTORIES(Graph Graph/stk)
    ADD_SUBDIRECTORY(Graph)
    ADD_SUBDIRECTORY(UI)

########## Top-level headers and files ##########

    SET(TOP_LEVEL_HEADERS Core.hpp Python.hpp)
    SET(TOP_LEVEL_FILES CMakeLists.txt checker.py)

    ADD_TO_GLOBAL_SOURCE_LIST(${TOP_LEVEL_HEADERS} ${TOP_LEVEL_FILES})

    INSTALL(FILES ${TOP_LEVEL_HEADERS} DESTINATION include/opensolid)
        
