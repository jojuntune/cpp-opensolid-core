########## Set up Eigen source tree ##########

    # Extract Eigen sources from tarball
    externalproject_add(
        eigen_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.2.0.tar.gz
        URL_MD5 7c04a56bab71a9a6f2ed0af57fb25491
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    # Add custom eigen_patch step to copy updated plugin headers into the Eigen
    # extraction directory if the plugin headers change. This will also trigger
    # a recompile of all targets that depend on Eigen (i.e., everything)
    externalproject_add_step(
        eigen_sources
        eigen_patch
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/patch.cmake
        DEPENDEES download
        DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/DenseBasePlugin.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MatrixBasePlugin.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MatrixPlugin.hpp
        WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources
    )
    
    # Store location of Eigen root include directory
    set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources)
    
    # Set EIGEN_ROOT in external/ directory (will then be passed up to root)
    set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)

########## Install Eigen headers ##########

    install(DIRECTORY ${EIGEN_ROOT}/Eigen DESTINATION include PATTERN CMakeLists.txt EXCLUDE)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
