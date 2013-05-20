find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Set up SWIG
set(CMAKE_SWIG_OUTDIR ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR})
set(CMAKE_SWIG_FLAGS -c++)

# Set up interface file
set(OPENSOLID_SWIG_FLAGS -namespace OpenSolid)
set_source_files_properties(
    OpenSolidDotNet.i
    PROPERTIES
    CPLUSPLUS ON
    SWIG_FLAGS "${OPENSOLID_SWIG_FLAGS}"
)

# Build extension DLL
swig_add_module(OpenSolidDotNet csharp OpenSolidDotNet.i)
#set_target_properties(OpenSolidDotNet PROPERTIES PREFIX "" SUFFIX ".dll")
swig_link_libraries(OpenSolidDotNet OpenSolidCore)

# Set up C# compiler
if(WIN32)
    find_program(CSHARP_COMPILER NAMES csc)
    set(CSHARP_COMPILER_ARGS /out:OpenSolid.dll /target:library)
else()
    find_program(CSHARP_COMPILER mcs dmcs)
    set(CSHARP_COMPILER_ARGS -out:OpenSolid.dll -t:library)
endif()

# Build .NET DLL
add_custom_target(
    OpenSolidDLL ALL
    ${CSHARP_COMPILER} ${CSHARP_COMPILER_ARGS} *.cs
    WORKING_DIRECTORY ${CMAKE_SWIG_OUTDIR}
)
add_dependencies(OpenSolidDLL OpenSolidDotNet)
