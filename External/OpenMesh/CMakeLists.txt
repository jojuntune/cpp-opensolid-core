# Set up OpenMesh compile flags
set(OPENMESH_CXX_FLAGS ${DISABLE_WARNINGS_FLAG})
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(OPENMESH_CXX_FLAGS "${OPENMESH_CXX_FLAGS} -DWIN32 /EHsc")
endif()

# Determine OpenMesh build type (Debug/Release)
set(OPENMESH_BUILD_TYPE)
if(DEFINED CMAKE_CONFIGURATION_TYPES)
    # Multiple-configuration generator (e.g., Visual Studio): use CMAKE_CFG_INTDIR meta-variable
    set(OPENMESH_BUILD_TYPE ${CMAKE_CFG_INTDIR})
else()
    # Single-configuration generator (e.g., makefile): use CMAKE_BUILD_TYPE variable
    set(OPENMESH_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

if(${BUILD_STATIC_CORE})
    set(OPENMESH_BUILD_SHARED OFF)
else()
    set(OPENMESH_BUILD_SHARED ON)
endif()

# Build and install OpenMesh
externalproject_add(
    OpenMesh
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    URL ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh-2.3.1-patched-minus-documentation.tar.gz
    URL_MD5 77d7705dfc65c9f513d5f28018a86f45
    CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${OPENMESH_BUILD_TYPE}
    -DOPENMESH_BUILD_SHARED=${OPENMESH_BUILD_SHARED}
    -DCMAKE_CXX_FLAGS=${OPENMESH_CXX_FLAGS}
    -DBUILD_APPS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/${OPENMESH_BUILD_TYPE}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/${OPENMESH_BUILD_TYPE}
)

# Set OPENMESH_INCLUDE in parent directory (will then be passed up to root)
set(OPENMESH_ROOT ${CMAKE_CURRENT_BINARY_DIR}/${OPENMESH_BUILD_TYPE} PARENT_SCOPE)

# Add files to global source list
add_to_global_source_list(*)
