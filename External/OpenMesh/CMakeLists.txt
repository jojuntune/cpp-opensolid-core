# Build and install OpenMesh
externalproject_add(
    OpenMesh
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    URL ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh-2.3.1-minus-documentation.tar.gz
    URL_MD5 caef3ef824c87b52c43274677a8a9d71
    CMAKE_ARGS
    -DCMAKE_CXX_FLAGS=${DISABLE_WARNINGS_FLAG}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DBUILD_APPS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/install
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
)

# Store location of OpenMesh root include directory
set(OPENMESH_ROOT ${CMAKE_CURRENT_BINARY_DIR}/install)

# Set OPENMESH_INCLUDE in external/ directory (will then be passed up to root)
set(OPENMESH_ROOT ${OPENMESH_ROOT} PARENT_SCOPE)

# Add files to global source list
add_to_global_source_list(*)
