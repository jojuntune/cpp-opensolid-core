add_executable(sandbox-syntax-examples sandbox-syntax-examples.cpp)
target_link_libraries(sandbox-syntax-examples OpenSolidCore)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Disable warnings about variables that are created (to show example syntax)
    # but never actually used
    set_target_properties(
        sandbox-syntax-examples
        PROPERTIES
        COMPILE_FLAGS "-Wno-unused-but-set-variable"
    )
endif()

add_executable(sandbox-spatialset-performance sandbox-spatialset-performance.cpp)
target_link_libraries(sandbox-spatialset-performance OpenSolidCore)
