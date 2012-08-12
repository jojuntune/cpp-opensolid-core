########## General setup ##########

    project(OpenSolid)
    
    # CMake 2.8.3 or later is required for CMAKE_CURRENT_LIST_DIR variable
    cmake_minimum_required(VERSION 2.8.3)

    # Include generic macros
    include(CreateSourceGroups.cmake)
    
########## Set up user configuration options ##########

    set(BUILD_IO_MODULE ON CACHE BOOL "Build I/O module")
    set(BUILD_PYTHON_MODULE ON CACHE BOOL "Build Python module (requires SWIG, Python)")
    set(BUILD_UI ON CACHE BOOL "Build UI (requires Qt, depends on Python module)")
    set(BUILD_TESTS ON CACHE BOOL "Build tests")
    set(BUILD_DOCUMENTATION ON CACHE BOOL "Build documentation (requires Doxygen)")
    
########## Set up common build settings ##########

    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    add_definitions(-D_USE_MATH_DEFINES)

    # Set up compiler-specific flags
    if (CMAKE_COMPILER_IS_GNUCXX)
        # Enable pthread
        add_definitions(-DHAVE_PTHREAD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
        # Set up warnings
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-variable -Wno-enum-compare")
        # Disable asserts in RelWithDebInfo build for efficiency
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
        # Enable -fpic on 64-bit systems where it is required
        if (CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
        endif ()
        # Define proper flag to enable C++11 features
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        if (GCC_VERSION VERSION_LESS 4.7)
            add_definitions(-std=c++0x)
        else ()
            add_definitions(-std=c++11)
        endif ()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_definitions(-DHAVE_PTHREAD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall -Wno-unused-function")
        set(CMAKE_EXE_LINKER_FLAGS "-pthread -ldl")
        set(CMAKE_SHARED_LINKER_FLAGS "-pthread -ldl")
        set(CMAKE_MODULE_LINKER_FLAGS "-pthread -ldl")
    elseif (MSVC)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        add_definitions(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
        # Add /MP flag for parallel compilation within projects
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        # Disable incremental linking (seems to cause erros in debug builds)
        set(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "/INCREMENTAL:NO")
        set(CMAKE_MODULE_LINKER_FLAGS "/INCREMENTAL:NO")
    endif ()
    
    # Include parent directory to allow for #include <opensolid/...>, and external directory to
    # allow for #include <Eigen/...> etc.
    include_directories(. external external/cxxtest)

    # Place all executables, libraries in one directory
    if (MSVC_IDE)
        set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
        set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    else ()
        set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
        set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
    endif ()
    
########## Build and install subprojects ##########

    # Set up external dependencies
    add_subdirectory(external)

    # Set up config header
    include_directories(config)
    add_subdirectory(config)
    
    # Build core library
    include_directories(core)
    add_subdirectory(core)
    
    # Build I/O module if selected
    if (${BUILD_IO_MODULE})
        include_directories(io)
        add_subdirectory(io)
    endif()
    
    # Build Python module if selected
    if (${BUILD_PYTHON_MODULE})
        include_directories(python)
        add_subdirectory(python)
    endif()
    
    # Build UI if selected
    if (${BUILD_UI})
        add_subdirectory(ui)
    endif()
    
    # Build tests if selected
    if (${BUILD_TESTS})
        add_subdirectory(tests)
    endif()
    
    # Build documentation if selected
    if (${BUILD_DOCUMENTATION})
        add_subdirectory(documentation EXCLUDE_FROM_ALL)
    endif()

########## Set up source groups for Visual Studio ##########

    create_source_groups()
    
########## Install license file ##########
    
    install(FILES license.txt DESTINATION "${CMAKE_INSTALL_PREFIX}")
