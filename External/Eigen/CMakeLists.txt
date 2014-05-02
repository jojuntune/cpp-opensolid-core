########## Set up Eigen source tree ##########

    # Extract Eigen sources from tarball
    externalproject_add(
        eigen_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.2.1.tar.gz
        URL_MD5 a0e0a32d62028218b1c1848ad7121476
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    
    # Store location of Eigen root include directory
    set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources)
    
    # Set EIGEN_ROOT in external/ directory (will then be passed up to root)
    set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
