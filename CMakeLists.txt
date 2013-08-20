########## General setup ##########

    project(OpenSolid)
    
    # CMake 2.8.3 or later is required for CMAKE_CURRENT_LIST_DIR variable
    cmake_minimum_required(VERSION 2.8.3)

    # Include macros for generating Visual Studio source groups
    include(CreateSourceGroups.cmake)
    
########## Set up user configuration options ##########

    set(BUILD_STATIC_CORE OFF CACHE BOOL "Build static core module")
    set(BUILD_MESH_MODULE OFF CACHE BOOL "Build mesh module")
    set(BUILD_IO_MODULE OFF CACHE BOOL "Build I/O module")
    set(BUILD_DART_MODULE OFF CACHE BOOL "Build Dart module (DART_SDK_DIR environment variable must be set)")
    set(BUILD_PYTHON_MODULE OFF CACHE BOOL "Build Python module")
    set(BUILD_TESTS OFF CACHE BOOL "Build tests for all enabled modules (requires Python)")
    set(BUILD_DOCUMENTATION OFF CACHE BOOL "Build documentation (requires Doxygen)")
    
########## Set up common build settings ##########

    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    add_definitions(-D_USE_MATH_DEFINES)

    # Add preprocessor definition for dynamic libraries to enable propery setup
    # of dllimport/dllexport in MSVC builds
    if (${BUILD_STATIC_CORE})
        add_definitions(-DOPENSOLID_BUILD_STATIC_CORE)
    endif()

    # Set up compiler-specific flags
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # Enable pthreads
        add_definitions(-DHAVE_PTHREAD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

        # Enable C++11 support
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        
        # Set up warnings
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-variable -Wno-enum-compare")
        
        # Disable asserts in RelWithDebInfo build for efficiency
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
        
        # Enable -fpic on 64-bit systems where it is required
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
        endif()

        # Initialize disable-warnings flag
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # Enable pthreads
        add_definitions(-DHAVE_PTHREAD)

        # Enable C++11 support
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        # Set up warnings
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function")

        # Enable dynamic loading
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -ldl")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -ldl")

        # Set up proper linking to low-level libraries on different platforms
        if(${APPLE})
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++")
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++")
            set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pthread")
            set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -pthread")
        endif()

        # Initialize disable-warnings flag
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        # Make sure min/max macros are not defined by windows.h (conflicts with
        # interval min/max and Eigen code), and avoid warning about boost
        # string algorithms
        add_definitions(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
        
        # Add /MP flag for parallel compilation within projects
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        
        # Disable incremental linking (seems to cause errors in debug builds)
        set(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "/INCREMENTAL:NO")
        set(CMAKE_MODULE_LINKER_FLAGS "/INCREMENTAL:NO")
        
        # Explicitly set WIN64 compiler flag and /MACHINE linker flag for 64-bit builds
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            add_definitions(-DWIN64)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MACHINE:x64")
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MACHINE:x64")
            set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MACHINE:x64")
        endif()

        # Initialize disable-warnings flag
        set(DISABLE_WARNINGS_FLAG "/w")
    else()
        message("Compiler type not detected!")
    endif()

    # Place all executables and libraries in one directory
    if(${MSVC_IDE})
        set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
        set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
        set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
    endif()
    
########## Build and install subprojects ##########
    
    # Set up Boost
    find_package(Boost REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})

    # Set up external dependencies
    add_subdirectory(External)

    # Include Eigen root directory to allow inclusion of Eigen headers
    include_directories(${EIGEN_ROOT})
    
    # Add root directory to include path to allow for #include <OpenSolid/...>
    include_directories(.)
    
    # Build core library
    add_subdirectory(OpenSolid/Core)
    
    # Build I/O module if selected
    if(${BUILD_IO_MODULE})
        include_directories(${PROTOBUF_ROOT})
        include_directories(${SQLITE_ROOT})
        add_subdirectory(OpenSolid/IO)
    endif()

    # Include OpenMesh include directory if mesh module is enabled
    if(${BUILD_MESH_MODULE})
        include_directories(${OPENMESH_ROOT}/include)
    endif()

    # Build Dart bindings if selected
    if(${BUILD_DART_MODULE})
        add_subdirectory(OpenSolid/Dart)
    endif()

    # Build Python bindings if selected
    if(${BUILD_PYTHON_MODULE})
        find_package(Boost REQUIRED COMPONENTS Python)
        find_package(PythonInterp REQUIRED)
        find_package(PythonLibs REQUIRED)
        include_directories(${PYTHON_INCLUDE_PATH})
        add_subdirectory(OpenSolid/Python)
    endif()
    
    # Build UI if selected
    if(${BUILD_UI})
        # Set up Qt
        find_package(Qt4 REQUIRED)
        set(QT_USE_QTOPENGL ON)
        set(QT_USE_QTXML ON)
        include(${QT_USE_FILE})
        include_directories(${QT_INCLUDE_DIR})
        add_definitions(${QT_DEFINITIONS})
        
        # Set up OpenGL
        find_package(OpenGL REQUIRED)
        include_directories(${OPENGL_INCLUDE_DIR})
        # Most POSIX systems have OpenGL headers in GL/ subdirectory
        include_directories(${OPENGL_INCLUDE_DIR}/GL)
        # Mac OS X has OpenGL headers in Headers/ subdirectory of framework
        # directory
        include_directories(${OPENGL_INCLUDE_DIR}/Headers)
    
        add_subdirectory(UI)
    endif()
    
    # Build tests if selected
    if(${BUILD_TESTS})
        # Need to call enable_testing at project root for testing to be enable
        # properly
        enable_testing()
        add_subdirectory(Tests)
    endif()
    
    # Build documentation if selected
    if(${BUILD_DOCUMENTATION})
        add_subdirectory(Documentation)
    endif()
    
########## Install files ##########
    
    install(FILES OpenSolid/config.hpp DESTINATION include/OpenSolid)
    install(FILES license.txt lgpl-2.1.txt gpl-2.txt DESTINATION "${CMAKE_INSTALL_PREFIX}")

########## Set up source groups for Visual Studio ##########

    add_to_global_source_list(* OpenSolid/*)
    create_source_groups()
