########## General setup ##########
    
    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    find_package(PythonInterp REQUIRED)
    
    include_directories(${CXXTEST_ROOT})
        
    # Create macro for adding a CxxTest/CTest-based test
    macro(add_cxxtest name source)
        get_source_file_property(FULL_PATH ${source} LOCATION)
        # Generate test source file
        add_custom_command(
            OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            DEPENDS
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

    if(${BUILD_CORE_MODULE})
        add_cxxtest(IntervalTests IntervalTests.hpp opensolid_core)
        add_cxxtest(MatrixTests MatrixTests.hpp opensolid_core)
        add_cxxtest(DatumTests DatumTests.hpp opensolid_core)
        add_cxxtest(SimplexTests SimplexTests.hpp opensolid_core)
        add_cxxtest(SetTests SetTests.hpp opensolid_core)
        add_cxxtest(FunctionTests FunctionTests.hpp opensolid_core)
        add_cxxtest(GeometryTests GeometryTests.hpp opensolid_core)
        
        add_to_global_source_list(
            IntervalTests.hpp
            MatrixTests.hpp
            DatumTests.hpp
            SimplexTests.hpp
            SetTests.hpp
            FunctionTests.hpp
            GeometryTests.hpp
        )
    endif()
    
########## Python module tests ##########
    
    if(${BUILD_PYTHON_MODULE})
        # Set up Python
        find_package(PythonLibs REQUIRED)
        include_directories(${PYTHON_INCLUDE_DIRS})

        add_cxxtest(PythonTests PythonTests.hpp opensolid_python)
        
        add_to_global_source_list(PythonTests.hpp)
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
