find_package(Doxygen)

# Directory for which documentation should be generated
set(SOURCE_DIR ${OpenSolid_SOURCE_DIR}/OpenSolid)

# Copy logo image to build directory
configure_file(images/logo-small.png ${CMAKE_CURRENT_BINARY_DIR}/logo-small.png COPYONLY)

# Replace references to CMake variables within Doxyfile.in with actual values
# (various paths to source files and directories)
configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Generate Doxygen documentation
add_custom_target(Documentation ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_to_global_source_list(* images/*)
