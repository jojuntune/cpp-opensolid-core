########## General setup ##########

    include(ExternalProject)

########## Build external projects where required by OpenSolid modules ##########
    
    if(${BUILD_IO_MODULE})
        add_subdirectory(SQLite)
        add_subdirectory(ProtocolBuffers)
        set(SQLITE_ROOT ${SQLITE_ROOT} PARENT_SCOPE)
        set(PROTOBUF_ROOT ${PROTOBUF_ROOT} PARENT_SCOPE)
    endif()

    if(${BUILD_MESH_MODULE})
        add_subdirectory(OpenMesh)
        set(OPENMESH_ROOT ${OPENMESH_ROOT} PARENT_SCOPE)
    endif()

    if(${BUILD_DART_MODULE})
        set(DART_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Dart PARENT_SCOPE)
    endif()
    
    if(${BUILD_TESTS})
        add_subdirectory(CxxTest)
        set(CXXTEST_ROOT ${CXXTEST_ROOT} PARENT_SCOPE)
        add_subdirectory(Catch)
        set(CATCH_ROOT ${CATCH_ROOT} PARENT_SCOPE)
    endif()
    
########## Add files to global source list ##########
    
    add_to_global_source_list(CMakeLists.txt)
