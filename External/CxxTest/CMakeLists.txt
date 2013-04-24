########## Set up CxxTest source tree ##########

    externalproject_add(
        cxxtest_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.2.1.tar.gz
        URL_MD5 d3bbba0fac5a61c594e2f7dd2321b91b
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    
    # Set CXXTEST_ROOT in external/ directory (will then be passed up to root)
    set(CXXTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/cxxtest_sources PARENT_SCOPE)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
