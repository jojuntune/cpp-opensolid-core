FIND_PACKAGE(Doxygen)

SET(SOURCE_DIR ${OpenSolid}/Core)

# Copy logo image to build directory
CONFIGURE_FILE(
    ${OpenSolid}/Documentation/Images/logo-small.png
    ${CMAKE_CURRENT_BINARY_DIR}/logo-small.png
    COPYONLY
)

# Replace references to CMake variables within Doxyfile.in with actual values
# (various paths to source files and directories)
CONFIGURE_FILE(
    ${OpenSolid}/Documentation/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
)

# Generate Doxygen documentation
ADD_CUSTOM_TARGET(documentation ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
