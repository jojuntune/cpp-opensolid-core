########## General setup ##########
    
    # Find Python interpreter (used to run source file checker script)
    find_package(PythonInterp REQUIRED)
    
    include_directories(${CATCH_ROOT})

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

    add_simple_test(CircleTests CircleTests.cpp OpenSolidCore)
    add_simple_test(CollectionTests CollectionTests.cpp OpenSolidCore)
    add_simple_test(CoordinateSystemTests CoordinateSystemTests.cpp OpenSolidCore)
    add_simple_test(CurveTests CurveTests.cpp OpenSolidCore)
    add_simple_test(DatumTests DatumTests.cpp OpenSolidCore)
    add_simple_test(IntervalTests IntervalTests.cpp OpenSolidCore)
    add_simple_test(MatrixTests MatrixTests.cpp OpenSolidCore)
    add_simple_test(ParametricExpressionTests ParametricExpressionTests.cpp OpenSolidCore) 
    add_simple_test(PositionTests PositionTests.cpp OpenSolidCore)
    add_simple_test(QuaternionTests QuaternionTests.cpp OpenSolidCore)
    add_simple_test(SetTests SetTests.cpp OpenSolidCore)
    add_simple_test(SimplexTests SimplexTests.cpp OpenSolidCore)
    add_simple_test(SphereTests SphereTests.cpp OpenSolidCore)
    add_simple_test(VectorTests VectorTests.cpp OpenSolidCore)
    
    add_to_global_source_list(
        CircleTests.cpp
        CollectionTests.cpp
        CoordinateSystemTests.cpp
        CurveTests.cpp
        DatumTests.cpp
        IntervalTests.cpp
        MatrixTests.cpp
        ParametricExpressionTests.cpp
        PositionTests.cpp
        QuaternionTests.cpp
        SetTests.cpp
        SimplexTests.cpp
        SphereTests.cpp
        VectorTests.cpp
    )

########## Scripting module tests ##########

    if(${BUILD_SCRIPTING_MODULE})
        add_simple_test(ScriptingTests ScriptingTests.cpp OpenSolidCore OpenSolidScripting)
        add_to_global_source_list(ScriptingTests.cpp)
    endif()
    
########## .NET binding tests ##########
    
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CSharpTests.cs CSHARP_TEST_NATIVE_PATH)

    if(${BUILD_DOTNET_BINDINGS})
        add_custom_target(
            CSharpTests ALL
            ${CSHARP_COMPILER}
            /r:OpenSolid.dll
            /out:${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/CSharpTests.exe
            ${CSHARP_TEST_NATIVE_PATH}
            WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
        )
        add_dependencies(CSharpTests OpenSolidDotNet)
    endif()
    
########## Java binding tests ##########

    if(${BUILD_JAVA_BINDINGS})
        set(CMAKE_JAVA_JAR_ENTRY_POINT ca/ianmackenzie/tests/JavaTests)
        add_jar(opensolid-tests SOURCES JavaTests.java INCLUDE_JARS opensolid)
    endif()
    
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
