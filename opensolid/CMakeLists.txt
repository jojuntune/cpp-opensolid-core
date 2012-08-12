########## Set up testing ##########

    # Find Python interpreter (used by CxxTest to generate test source files, and to run source
    # file checker script)
    find_package(PythonInterp REQUIRED)
    
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
            "${OpenSolid_SOURCE_DIR}/external/cxxtest/bin/cxxtestgen"
            --error-printer
            -o "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp"
            "${FULL_PATH}"
        )

        # Create test executable
        add_executable(${name} "${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp")

        # Link test executable to any libraries specified as additional macro arguments
        target_link_libraries(${name} ${ARGN})

        # Register executable as a test
        add_test(${name} "${EXECUTABLE_OUTPUT_PATH}/${name}")
    endmacro(add_cxxtest)
    
    # Add global source-checking test
    add_test(SourceChecks
        "${PYTHON_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/checker.py"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    
########## Build and install subprojects ##########

    add_subdirectory(core)
    add_subdirectory(python)

    include_directories(graph graph/stk)
    add_subdirectory(graph)
    add_subdirectory(ui)

########## Add files to global source list ##########

    add_to_global_source_list(    
        checker.py
        CMakeLists.txt
        config.hpp
        Template.cpp
        Template.hpp
        TemplateTests.hpp
    )
