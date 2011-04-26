FIND_PACKAGE(Doxygen)

# Copy logo image to build directory
CONFIGURE_FILE(Images/logo-small.png ${OpenSolid_BINARY_DIR}/doc/logo-small.png COPYONLY)

# Replace references to CMake variables within Doxyfile.in with actual values
# (various paths to source files and directories)
CONFIGURE_FILE(Doxyfile.in ${OpenSolid_BINARY_DIR}/doc/Doxyfile)

# Generate Doxygen documentation
ADD_CUSTOM_TARGET(doc ${DOXYGEN_EXECUTABLE} ${OpenSolid_BINARY_DIR}/doc/Doxyfile)
