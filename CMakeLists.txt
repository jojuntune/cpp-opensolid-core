########## General setup ##########

    PROJECT(OpenSolid)
    
    # CMake 2.8.3 or later is required for CMAKE_CURRENT_LIST_DIR variable
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

    # Include generic macros
    INCLUDE(macros.cmake)

########## Define minimal preprocessor definitions ##########

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
