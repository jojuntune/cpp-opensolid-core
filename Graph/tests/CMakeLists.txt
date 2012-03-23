# Graph Tests.

ADD_EXECUTABLE( nodeTests nodeTests.cpp )
TARGET_LINK_LIBRARIES( nodeTests OpenSolidGraph )
ADD_TEST( graph_node_tests ${EXECUTABLE_OUTPUT_PATH}/nodeTests )

SET(GLOBAL_SOURCE_LIST
    ${GLOBAL_SOURCE_LIST}
    "${OpenSolid}/Graph/tests/nodeTests.cpp"
    "${OpenSolid}/Graph/tests/CMakeLists.txt"
    PARENT_SCOPE
)

#ADD_EXECUTABLE( evalTests evalTests.cpp )
#TARGET_LINK_LIBRARIES( evalTests opensolid_graph )
#ADD_TEST( graph_eval_tests ${EXECUTABLE_OUTPUT_PATH}/evalTests )
