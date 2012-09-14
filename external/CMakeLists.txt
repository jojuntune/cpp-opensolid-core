########## General setup ##########

    include(ExternalProject)    

    # Set up flag to use to disable compiler warnings on external code
    set(DISABLE_WARNINGS_FLAG "")
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif (MSVC)
        set(DISABLE_WARNINGS_FLAG "/w")
    endif ()

########## Set up Eigen ##########

    # Extract Eigen sources
    externalproject_add(
        eigen_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.1.1.tar.gz
        URL_MD5 7f1de87d4bfef65d0c59f15f6697829d
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources)
    
    # Set EIGEN_ROOT in parent scope so it can be used as an include dir
    set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)
    
    # Install Eigen headers
    install(DIRECTORY ${EIGEN_ROOT}/Eigen DESTINATION include PATTERN CMakeLists.txt EXCLUDE)

########## Set up CxxTest (if testing is enabled) ##########

    if (${BUILD_TESTS})
        externalproject_add(
            cxxtest_sources
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}
            URL ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.0.2.tar.gz
            URL_MD5 8fac08cb5300d74f054cffdd2466a5d3
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )
        set(CXXTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/cxxtest_sources PARENT_SCOPE)
    endif()

########## Extract and build SQLite ##########

    if (${BUILD_IO_MODULE})
        externalproject_add(
            sqlite_sources
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}
            URL ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-3.7.13.tar.gz
            URL_MD5 3318320154a6e00cd50e7746e81f89df
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )
        set(SQLITE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/sqlite_sources)
        
        # Build SQLite static library
        add_library(sqlite_library STATIC ${SQLITE_ROOT}/sqlite3.c)
        set_target_properties(sqlite_library PROPERTIES OUTPUT_NAME sqlite3 DEBUG_POSTFIX _debug)
        set_source_files_properties(${SQLITE_ROOT}/sqlite3.c PROPERTIES GENERATED TRUE)
        add_dependencies(sqlite_library sqlite_sources)
        if (CMAKE_COMPILER_IS_GNUCXX)
            find_package(Threads)
            target_link_libraries(sqlite_library dl ${CMAKE_THREAD_LIBS_INIT})
        endif ()
    
        # Build SQLite shell
        add_executable(sqlite_shell ${SQLITE_ROOT}/shell.c)
        set_target_properties(sqlite_shell PROPERTIES OUTPUT_NAME sqlite3)
        set_source_files_properties(${SQLITE_ROOT}/shell.c PROPERTIES GENERATED TRUE)
        add_dependencies(sqlite_shell sqlite_sources)
        target_link_libraries(sqlite_shell sqlite_library)
        
        # Disable compiler warnings for SQLite code
        set_target_properties(
            sqlite_library
            sqlite_shell
            PROPERTIES
            COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG}
        )
    endif ()

########## Define lists of source files ##########
    
    add_to_global_source_list(CMakeLists.txt)
