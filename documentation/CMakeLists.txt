find_package(Doxygen)

set(SOURCE_DIR ${OpenSolid_SOURCE_DIR}/source/core/opensolid)

# Copy logo image to build directory
configure_file(images/logo-small.png ${CMAKE_CURRENT_BINARY_DIR}/logo-small.png COPYONLY)

# Replace references to CMake variables within Doxyfile.in with actual values
# (various paths to source files and directories)
configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Generate Doxygen documentation
add_custom_target(documentation ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_to_global_source_list(CMakeLists.txt Doxyfile.in mainpage.dox)
