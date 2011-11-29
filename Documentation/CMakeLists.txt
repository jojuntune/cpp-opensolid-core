PROJECT(Documentation)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Doxygen)

SET(SOURCE_DIR ${Documentation_SOURCE_DIR}/../OpenSolid)

# Copy logo image to build directory
CONFIGURE_FILE(Images/logo-small.png ${Documentation_BINARY_DIR}/logo-small.png COPYONLY)

# Replace references to CMake variables within Doxyfile.in with actual values
# (various paths to source files and directories)
CONFIGURE_FILE(Doxyfile.in ${Documentation_BINARY_DIR}/Doxyfile)

# Generate Doxygen documentation
ADD_CUSTOM_TARGET(documentation ${DOXYGEN_EXECUTABLE} ${Documentation_BINARY_DIR}/Doxyfile)
