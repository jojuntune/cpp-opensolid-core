########## Set up Eigen source tree ##########

    externalproject_add(
        eigen_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.1.1.tar.gz
        URL_MD5 7f1de87d4bfef65d0c59f15f6697829d
        PATCH_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/patch.cmake
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources)
    
    # Set EIGEN_ROOT in external/ directory (will then be passed up to root)
    set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)

########## Install Eigen headers ##########

    install(DIRECTORY ${EIGEN_ROOT}/Eigen DESTINATION include PATTERN CMakeLists.txt EXCLUDE)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
