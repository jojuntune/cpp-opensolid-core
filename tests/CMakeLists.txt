# Enable testing using CTest
enable_testing()
    
# Graph tests
add_executable(nodeTests nodeTests.cpp)
target_link_libraries(nodeTests opensolid_graph)
add_test(graph_node_tests ${EXECUTABLE_OUTPUT_PATH}/nodeTests)

add_to_global_source_list(CMakeLists.txt nodeTests.cpp)

#ADD_EXECUTABLE( evalTests evalTests.cpp )
#TARGET_LINK_LIBRARIES( evalTests opensolid_graph )
#ADD_TEST( graph_eval_tests ${EXECUTABLE_OUTPUT_PATH}/evalTests )
