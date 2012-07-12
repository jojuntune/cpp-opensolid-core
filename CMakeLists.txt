########## General setup ##########

    PROJECT(OpenSolid)
    
    # CMake 2.8.3 or later is required for CMAKE_CURRENT_LIST_DIR variable
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

    # Include generic macros
    INCLUDE(macros.cmake)
    
    # Enable testing using CTest
    ENABLE_TESTING()
    
########## Set up common compiler settings ##########

    # Set up compiler-specific flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Enable C++11 and pthread and add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall -Wno-unused-variable")
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
    INCLUDE_DIRECTORIES(. External)

    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
    
########## Build and install subprojects ##########

    ADD_SUBDIRECTORY(External)
    ADD_SUBDIRECTORY(opensolid)
    ADD_SUBDIRECTORY(Documentation EXCLUDE_FROM_ALL)

########## Set up source groups for Visual Studio ##########

    CREATE_SOURCE_GROUPS()
    
########## Install license file ##########
    
    INSTALL(FILES license.txt DESTINATION "${CMAKE_INSTALL_PREFIX}")
