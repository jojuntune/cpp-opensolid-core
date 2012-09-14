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
message("${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources")
set(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/eigen_sources)
set(EIGEN_ROOT ${EIGEN_ROOT} PARENT_SCOPE)

set(EIGEN_PLUGIN_HEADERS DenseBasePlugin.hpp MatrixBasePlugin.hpp MatrixPlugin.hpp)

# Copy Eigen plugin headers into the same directory as the corresponding Eigen headers
file(COPY ${EIGEN_PLUGIN_HEADERS} DESTINATION ${EIGEN_ROOT}/Eigen/src/Core)

# Install Eigen headers
install(DIRECTORY ${EIGEN_ROOT}/Eigen DESTINATION include PATTERN CMakeLists.txt EXCLUDE)

# Install Eigen plugin headers
install(FILES ${EIGEN_PLUGIN_HEADERS} DESTINATION include/Eigen/src/Core)
