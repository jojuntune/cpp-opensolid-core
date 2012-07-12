# Graph Tests.

ADD_EXECUTABLE( nodeTests nodeTests.cpp )
TARGET_LINK_LIBRARIES( nodeTests OpenSolidGraph )
ADD_TEST( graph_node_tests ${EXECUTABLE_OUTPUT_PATH}/nodeTests )

ADD_TO_GLOBAL_SOURCE_LIST(CMakeLists.txt nodeTests.cpp)

#ADD_EXECUTABLE( evalTests evalTests.cpp )
#TARGET_LINK_LIBRARIES( evalTests opensolid_graph )
#ADD_TEST( graph_eval_tests ${EXECUTABLE_OUTPUT_PATH}/evalTests )
   
# Temporary fix - define 'override' as empty macro for GCC < 4.7    
IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
    SET_TARGET_PROPERTIES(
        nodeTests
        PROPERTIES
        COMPILE_FLAGS
        "-Doverride="
    )
ENDIF()
