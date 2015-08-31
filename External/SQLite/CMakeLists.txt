########## Set up SQLite source tree ##########

    # Extract SQLite sources from tarball
    externalproject_add(
        sqlite_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-3.8.1.tar.gz
        URL_MD5 e3ae0eeccb9953724b0bcf8a8964cbd4
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    # Store location of SQLite root include directory
    set(SQLITE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/sqlite_sources)
    
    # Set SQLITE_ROOT in external/ directory (will then be passed up to root)
    set(SQLITE_ROOT ${SQLITE_ROOT} PARENT_SCOPE)

########## Build SQLite library ##########

    add_library(sqlite_library STATIC ${SQLITE_ROOT}/sqlite3.c)
    set_target_properties(sqlite_library PROPERTIES OUTPUT_NAME sqlite3_static DEBUG_POSTFIX _debug)
    set_source_files_properties(${SQLITE_ROOT}/sqlite3.c PROPERTIES GENERATED TRUE)
    add_dependencies(sqlite_library sqlite_sources)
    if(${CMAKE_COMPILER_IS_GNUCXX})
        find_package(Threads)
        target_link_libraries(sqlite_library dl ${CMAKE_THREAD_LIBS_INIT})
    endif()
    set_target_properties(sqlite_library PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
    
########## Build SQLite shell ##########

    add_executable(sqlite_shell ${SQLITE_ROOT}/shell.c)
    set_target_properties(sqlite_shell PROPERTIES OUTPUT_NAME sqlite3)
    set_source_files_properties(${SQLITE_ROOT}/shell.c PROPERTIES GENERATED TRUE)
    add_dependencies(sqlite_shell sqlite_sources)
    target_link_libraries(sqlite_shell sqlite_library)
    set_target_properties(sqlite_shell PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
