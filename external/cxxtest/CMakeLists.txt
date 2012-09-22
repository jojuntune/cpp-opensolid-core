########## Define lists of source files ##########

    add_to_global_source_list(*)

########## Set up CxxTest source tree ##########

    externalproject_add(
        cxxtest_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.0.2.tar.gz
        URL_MD5 8fac08cb5300d74f054cffdd2466a5d3
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    
    # Set CXXTEST_ROOT in external/ directory (will then be passed up to root)
    set(CXXTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/cxxtest_sources PARENT_SCOPE)
