# Set CXXTEST_ROOT in external/ directory (will then be passed up to root)
set(CATCH_ROOT ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
    
# Add files to global source list
add_to_global_source_list(CMakeLists.txt catch/catch.hpp)
