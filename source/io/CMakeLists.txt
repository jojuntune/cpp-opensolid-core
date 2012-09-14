########## Define lists of source files ##########

    file(GLOB HEADERS *.hpp)
    file(GLOB SOURCES *.cpp)
    
    # Update global source list
    add_to_global_source_list(${HEADERS} ${SOURCES} CMakeLists.txt ObjectMessage.proto)
    
########## Compile opensolid_io library ##########

    add_library(opensolid_io SHARED ${SOURCES} ${DETAIL_SOURCES})
    set_target_properties(opensolid_io PROPERTIES DEBUG_POSTFIX _debug)
    target_link_libraries(opensolid_io opensolid_core)
    
########## Install headers ##########
    
    install(DIRECTORY . DESTINATION include/opensolid FILES_MATCHING PATTERN *.hpp)
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    install(
        TARGETS opensolid_io
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
