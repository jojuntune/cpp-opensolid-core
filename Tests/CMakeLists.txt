########## General setup ##########
    
    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    find_package(PythonInterp REQUIRED)
    
    include_directories(${CXXTEST_ROOT})
    include_directories(${CATCH_ROOT})
        
    # Create macro for adding a CxxTest/CTest-based test
    macro(add_cxxtest name source)
        get_source_file_property(FULL_PATH ${source} LOCATION)
        # Generate test source file
        add_custom_command(
            OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            DEPENDS
            "${FULL_PATH}"
            IMPLICIT_DEPENDS
            "${FULL_PATH}"
            COMMAND
            "${PYTHON_EXECUTABLE}"
            ARGS
            "${CXXTEST_ROOT}/bin/cxxtestgen"
            --error-printer
            -o "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            "${FULL_PATH}"
        )
    
        # Create test executable
        add_executable(${name} "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp")
    
        # Link test executable to any libraries specified as additional macro arguments
        target_link_libraries(${name} ${ARGN})
        add_dependencies(${name} cxxtest_sources) 
    
        # Register executable as a test
        add_test(${name} "${EXECUTABLE_OUTPUT_PATH}/${name}")
    endmacro(add_cxxtest)

    macro(add_simple_test test_name test_source)
        add_executable(${test_name} ${test_source})
        target_link_libraries(${test_name} ${ARGN})
        add_test(NAME ${test_name} COMMAND ${test_name})
    endmacro(add_simple_test)

    # Configure all Catch test source files to define a main() function
    add_definitions(-DCATCH_CONFIG_MAIN)
    
    add_to_global_source_list(CMakeLists.txt Template.hpp)

########## Global source-checking test ##########

    add_test(
        SourceChecks
        "${PYTHON_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/checker.py"
        "${OpenSolid_SOURCE_DIR}"
    )

    add_to_global_source_list(checker.py)
    
########## Core module tests ##########

    add_simple_test(IntervalTests IntervalTests.cpp OpenSolidCore)
    add_simple_test(MatrixTests MatrixTests.cpp OpenSolidCore)
    add_simple_test(VectorTests VectorTests.cpp OpenSolidCore)
    add_simple_test(PositionTests PositionTests.cpp OpenSolidCore)
    add_simple_test(QuaternionTests QuaternionTests.cpp OpenSolidCore)
    add_simple_test(CoordinateSystemTests CoordinateSystemTests.cpp OpenSolidCore)

    add_cxxtest(SimplexTests SimplexTests.hpp OpenSolidCore)
    add_cxxtest(SetTests SetTests.hpp OpenSolidCore)
    add_cxxtest(ParametricExpressionTests ParametricExpressionTests.hpp OpenSolidCore)
    add_cxxtest(CurveTests CurveTests.hpp OpenSolidCore)
    add_cxxtest(CollectionTests CollectionTests.hpp OpenSolidCore)
    add_cxxtest(DatumTests DatumTests.hpp OpenSolidCore)
    
    add_to_global_source_list(
        IntervalTests.cpp
        MatrixTests.cpp
        VectorTests.cpp
        PositionTests.hpp
        CoordinateSystemTests.hpp
        SimplexTests.hpp
        SetTests.hpp
        ParametricExpressionTests.hpp
        CurveTests.hpp
        CollectionTests.hpp
        DatumTests.hpp
    )
    
########## Graph library tests ##########

    if(${BUILD_UI})
        # Add graph tests
        add_executable(nodeTests nodeTests.cpp)
        target_link_libraries(nodeTests opensolid_graph)
        add_test(graph_node_tests ${EXECUTABLE_OUTPUT_PATH}/nodeTests)
        
        #ADD_EXECUTABLE( evalTests evalTests.cpp )
        #TARGET_LINK_LIBRARIES( evalTests opensolid_graph )
        #ADD_TEST( graph_eval_tests ${EXECUTABLE_OUTPUT_PATH}/evalTests )
        
        add_to_global_source_list(nodeTests.cpp)
    endif()
