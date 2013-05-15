find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(CMAKE_SWIG_OUTDIR ${LIBRARY_OUTPUT_PATH})
set(CMAKE_SWIG_FLAGS "-c++")

set(INTERFACE_FILES opensolid_python.i opensolid_ruby.i OpenSolidCSharp.i)

set_source_files_properties(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)

if(${BUILD_PYTHON_BINDINGS})
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_PATH})

    swig_add_module(opensolid_python python opensolid_python.i)
    swig_link_libraries(opensolid_python ${PYTHON_LIBRARIES} OpenSolidCore)
endif()

if(${BUILD_RUBY_BINDINGS})
    find_package(Ruby REQUIRED)
    include_directories(${RUBY_INCLUDE_DIRS})

    # Get extension to use for Ruby native extension modules (e.g., 'bundle' on OS X)
    execute_process(
        COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print Config::CONFIG['DLEXT']"
        OUTPUT_VARIABLE RUBY_MODULE_EXTENSION
    )

    # Set up proper Ruby module name
    swig_add_module(opensolid_ruby ruby opensolid_ruby.i)
    set_target_properties(
        opensolid_ruby
        PROPERTIES
        PREFIX ""
        SUFFIX ".${RUBY_MODULE_EXTENSION}"
    )

    swig_link_libraries(opensolid_ruby ${RUBY_LIBRARY} OpenSolidCore)
endif()

if(${BUILD_CSHARP_BINDINGS})
    swig_add_module(OpenSolidCSharp csharp OpenSolidCSharp.i)
    swig_link_libraries(OpenSolidCSharp OpenSolidCore)
endif()
