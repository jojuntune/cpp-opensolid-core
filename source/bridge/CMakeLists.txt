########## Define lists of source files ##########

    file(GLOB HEADERS opensolid/*.hpp)
    file(GLOB SOURCES opensolid/*.cpp)
    
    # Update global source list
    add_to_global_source_list(
        ${HEADERS}
        ${SOURCES}
        CMakeLists.txt
    )
    
########## Compile OpenSolidCore library ##########

    add_library(opensolid_bridge SHARED ${SOURCES})
    set_target_properties(opensolid_core PROPERTIES DEBUG_POSTFIX _debug)
    add_dependencies(opensolid_bridge opensolid_core)
    
########## Install headers ##########
    
    install(
        DIRECTORY opensolid
        DESTINATION include/opensolid
        FILES_MATCHING
        PATTERN *.hpp
    )
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    install(
        TARGETS opensolid_bridge
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
