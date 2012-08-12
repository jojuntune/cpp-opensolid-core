########## General setup ##########

    include(ExternalProject)    

    # Set up flag to use to disable compiler warnings on external code
    set(DISABLE_WARNINGS_FLAG "")
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif (MSVC)
        set(DISABLE_WARNINGS_FLAG "/w")
    endif()

########## Set up Eigen ##########

    externalproject_add(
        Eigen
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/eigen-3.1.1.tar.gz
        URL_MD5 7f1de87d4bfef65d0c59f15f6697829d
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
    set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/Eigen PARENT_SCOPE)
    
    install(
        DIRECTORY ${EIGEN_ROOT}/Eigen
        DESTINATION include
        PATTERN "CMakeLists.txt" EXCLUDE
    )

########## Set up CxxTest (if testing is enabled) ##########

    if (${BUILD_TESTS})
        externalproject_add(
            CxxTest
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}
            URL ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.0.2.tar.gz
            URL_MD5 8fac08cb5300d74f054cffdd2466a5d3
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )
        set(CXXTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/CxxTest PARENT_SCOPE)
    endif()

########## Extract and build SQLite ##########

    if (${BUILD_IO_MODULE})
        externalproject_add(
            SQLite
            PREFIX ${SQLITE_OUTPUT_DIR}
            URL ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-3.7.13.tar.gz
            URL_MD5 3318320154a6e00cd50e7746e81f89df
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
        )
        set(SQLITE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/SQLite)
        
        # Build SQLite static library
        ADD_LIBRARY(libsqlite3 STATIC ${SQLITE_ROOT}/sqlite3.c)
        IF (CMAKE_COMPILER_IS_GNUCXX)
            FIND_PACKAGE(Threads)
            TARGET_LINK_LIBRARIES(libsqlite3 dl ${CMAKE_THREAD_LIBS_INIT})
        ENDIF ()
    
        # Build SQLite shell
        ADD_EXECUTABLE(sqlite3 ${SQLITE_ROOT}/shell.c)
        TARGET_LINK_LIBRARIES(sqlite3 libsqlite3)
        
        # Disable compiler warnings for SQLite code
        SET_TARGET_PROPERTIES(libsqlite3 sqlite3 PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
    endif()

########## Define lists of source files ##########
    
    ADD_TO_GLOBAL_SOURCE_LIST(CMakeLists.txt)
