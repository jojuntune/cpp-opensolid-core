########## Set up CxxTest source tree ##########

    externalproject_add(
        cxxtest_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.2.1-patched.tar.gz
        URL_MD5 f80b7b3daaf0c1e20ec2d62dce06a602
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    
    # Set CXXTEST_ROOT in external/ directory (will then be passed up to root)
    set(CXXTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/cxxtest_sources PARENT_SCOPE)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
