########## Define lists of source files ##########

    file(GLOB HEADERS *.hpp detail/*.hpp)
    file(GLOB SOURCES *.cpp detail/*.cpp)
    
    # Update global source list
    add_to_global_source_list(${HEADERS} ${SOURCES} CMakeLists.txt)

########## Copy Eigen plugin headers to temporary install directory ##########

    set(
        EIGEN_PLUGIN_HEADERS
        detail/DenseBasePlugin.hpp
        detail/MatrixBasePlugin.hpp
        detail/MatrixPlugin.hpp
    )
    file(COPY ${EIGEN_PLUGIN_HEADERS} DESTINATION ${EIGEN_ROOT}/opensolid/detail)
    
########## Compile OpenSolidCore library ##########

    add_library(opensolid_core SHARED ${SOURCES} ${DETAIL_SOURCES})
    set_target_properties(opensolid_core PROPERTIES DEBUG_POSTFIX _debug)
    add_dependencies(opensolid_core eigen_sources)
    
########## Install headers ##########
    
    install(DIRECTORY . DESTINATION include/opensolid FILES_MATCHING PATTERN *.hpp)
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    install(
        TARGETS opensolid_core
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
