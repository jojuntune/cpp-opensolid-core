########## Set up flag to use to disable compiler warnings on external code ##########
    
    set(DISABLE_WARNINGS_FLAG)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif (MSVC)
        set(DISABLE_WARNINGS_FLAG "/w")
    endif()

########## Set up Eigen ##########

    set(EIGEN_VERSION 3.1.1)
    set(EIGEN_REV 43d9075b23ef)
    
    # Extract Eigen source files
    set(EIGEN_ARCHIVE ${CMAKE_CURRENT_SOURCE_DIR}/eigen-${EIGEN_VERSION}.tar.gz)
    set(EIGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/eigen-${EIGEN_VERSION})
    add_custom_command(
        OUTPUT
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${EIGEN_ARCHIVE}
        DEPENDS ${EIGEN_ARCHIVE}
        WORKING_DIRECTORY ${EIGEN_OUTPUT_DIR}
        COMMENT "Extracting Eigen sources"
    )
    
    set(EIGEN_ROOT ${EIGEN_OUTPUT_DIR}/eigen-eigen-${EIGEN_REV} PARENT_SCOPE)
    
    INSTALL(
        DIRECTORY ${EIGEN}
        DESTINATION include
        PATTERN "CMakeLists.txt" EXCLUDE
    )

########## Set up CxxTest (if testing is enabled) ##########

    if (${BUILD_TESTS})
        set(CXXTEST_VERSION 4.0.2)
        
        # Extract CxxTest source files
        set(CXXTEST_ARCHIVE ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-${CXXTEST_VERSION}.tar.gz)
        set(CXXTEST_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/cxxtest-${CXXTEST_VERSION})
        add_custom_command(
            OUTPUT
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${CXXTEST_ARCHIVE}
            DEPENDS ${CXXTEST_ARCHIVE}
            WORKING_DIRECTORY ${CXXTEST_OUTPUT_DIR}
            COMMENT "Extracting CxxTest sources"
        )
        
        set(CXXTEST_ROOT ${CXXTEST_OUTPUT_DIR}/cxxtest PARENT_SCOPE)
    endif()

########## Extract and build SQLite ##########

    if (${BUILD_IO_MODULE})
        set(SQLITE_VERSION 3.7.13)
        set(SQLITE_VERSION_ENCODED 3071300)
        
        # Extract SQLite source files
        set(SQLITE_ARCHIVE ${CMAKE_CURRENT_SOURCE_DIR}/sqlite-${SQLITE_VERSION}.tar.gz)
        set(SQLITE_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/sqlite-${SQLITE_VERSION})
        set(SQLITE_AMALGAMATION_DIR ${SQLITE_OUTPUT_DIR}/sqlite-amalgamation-${SQLITE_VERSION_ENCODED})
        add_custom_command(
            OUTPUT
            ${SQLITE_AMALGAMATION_DIR}/sqlite3.c
            ${SQLITE_AMALGAMATION_DIR}/shell.c
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${SQLITE_ARCHIVE}
            DEPENDS ${SQLITE_ARCHIVE}
            WORKING_DIRECTORY ${SQLITE_OUTPUT_DIR}
            COMMENT "Extracting CxxTest sources"
        )
        
        # Build SQLite static library
        ADD_LIBRARY(libsqlite3 STATIC ${SQLITE_AMALGAMATION_DIR}/sqlite3.c)
        IF (CMAKE_COMPILER_IS_GNUCXX)
            FIND_PACKAGE(Threads)
            TARGET_LINK_LIBRARIES(libsqlite3 dl ${CMAKE_THREAD_LIBS_INIT})
        ENDIF ()
    
        # Build SQLite shell
        ADD_EXECUTABLE(sqlite3 ${SQLITE_AMALGAMATION_DIR}/shell.c)
        TARGET_LINK_LIBRARIES(sqlite3 libsqlite3)
        
        # Disable compiler warnings for SQLite code
        SET_TARGET_PROPERTIES(libsqlite3 sqlite3 PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
    endif()

########## Define lists of source files ##########
    
    ADD_TO_GLOBAL_SOURCE_LIST(CMakeLists.txt)
