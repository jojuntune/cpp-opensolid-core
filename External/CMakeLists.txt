########## General setup ##########

    include(ExternalProject)

########## Set up flag to use to disable compiler warnings on external code ##########

    set(DISABLE_WARNINGS_FLAG "")
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(DISABLE_WARNINGS_FLAG "-w")
    elseif(MSVC)
        set(DISABLE_WARNINGS_FLAG "/w")
    endif()
    
########## Build external projects where required by OpenSolid modules ##########

    if(${BUILD_CORE_MODULE})
        add_subdirectory(Eigen)
        set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)
    endif()
    
    if(${BUILD_IO_MODULE})
        add_subdirectory(SQLite)
        add_subdirectory(ProtocolBuffers)
        set(SQLITE_ROOT ${SQLITE_ROOT} PARENT_SCOPE)
        set(PROTOBUF_ROOT ${PROTOBUF_ROOT} PARENT_SCOPE)
    endif()
    
    if(${BUILD_TESTS})
        add_subdirectory(CxxTest)
        set(CXXTEST_ROOT ${CXXTEST_ROOT} PARENT_SCOPE)
    endif()
    
########## Add files to global source list ##########
    
    add_to_global_source_list(CMakeLists.txt)
