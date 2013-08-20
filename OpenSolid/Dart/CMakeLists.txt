# Check for valid DART_SDK_DIR environment variable
if(NOT EXISTS "$ENV{DART_SDK_DIR}/include/dart_api.h")
    message(SEND_ERROR "DART_SDK_DIR environment variable is not set to a valid Dart SDK directory")
    return()
endif()

include_directories("$ENV{DART_SDK_DIR}/include")

file(GLOB EXTENSION_SOURCES *.cpp)

# Build Dart extension library
add_library(opensolid_extension SHARED ${EXTENSION_SOURCES})
set_target_properties(opensolid_extension PROPERTIES DEBUG_POSTFIX _debug)
if (${WIN32})
    add_definitions(-DDART_SHARED_LIB)
    find_library(DART_LIBRARY dart "${DART_SDK_DIR}/lib")
    target_link_libraries(opensolid_extension OpenSolidCore ${DART_LIBRARY})
else ()
    target_link_libraries(opensolid_extension OpenSolidCore)
endif()

# Copy Dart library sources to build directory
file(GLOB DART_SOURCES *.dart)
add_custom_target(CopyDartSources ALL)
foreach(DART_SOURCE_FILE ${DART_SOURCES})
    add_custom_command(
        TARGET CopyDartSources
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DART_SOURCE_FILE} $<TARGET_FILE_DIR:opensolid_extension>
    )
endforeach()

add_to_global_source_list(*)
