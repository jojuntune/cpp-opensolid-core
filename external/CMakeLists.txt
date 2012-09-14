include(ExternalProject)

file(GLOB_RECURSE ALL_FILES *)
add_to_global_source_list(${ALL_FILES}) 

# Set up flag to use to disable compiler warnings on external code
set(DISABLE_WARNINGS_FLAG "")
if (CMAKE_COMPILER_IS_GNUCXX)
    set(DISABLE_WARNINGS_FLAG "-w")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(DISABLE_WARNINGS_FLAG "-w")
elseif (MSVC)
    set(DISABLE_WARNINGS_FLAG "/w")
endif ()

add_to_global_source_list(CMakeLists.txt)

if (${BUILD_CORE_MODULE})
    add_subdirectory(eigen)
    set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)
endif ()

if (${BUILD_IO_MODULE})
    add_subdirectory(sqlite)
    add_subdirectory(protobuf)
    set(SQLITE_ROOT ${SQLITE_ROOT} PARENT_SCOPE)
endif ()

if (${BUILD_TESTS})
    add_subdirectory(cxxtest)
    set(CXXTEST_ROOT ${CXXTEST_ROOT} PARENT_SCOPE)
endif ()
