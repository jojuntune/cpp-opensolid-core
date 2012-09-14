file(GLOB HEADERS *.hpp)
file(GLOB SOURCES *.cpp)

add_to_global_source_list(${HEADERS} ${SOURCES} CMakeLists.txt)

install(DIRECTORY . DESTINATION include/opensolid FILES_MATCHING PATTERN *.hpp)
