find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Set up SWIG
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_SWIG_FLAGS -c++)

# Set up interface file
set(OPENSOLID_SWIG_FLAGS -namespace OpenSolid -dllimport OpenSolidPInvoke)
set_source_files_properties(
    OpenSolid.i
    PROPERTIES
    CPLUSPLUS ON
    SWIG_FLAGS "${OPENSOLID_SWIG_FLAGS}"
)

# Build extension DLL
set(
    SWIG_MODULE_OpenSolidPInvoke_EXTRA_DEPS
    Interval.i
    Interval.hpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
swig_add_module(OpenSolidPInvoke csharp OpenSolid.i)
swig_link_libraries(OpenSolidPInvoke OpenSolidCore)

# Create list of C# source files to be compiled into OpenSolid .NET DLL
set(
    CSHARP_SOURCE_FILES
    ${CMAKE_SWIG_OUTDIR}/OpenSolidPINVOKE.cs
    ${CMAKE_SWIG_OUTDIR}/OpenSolid.cs
    ${CMAKE_SWIG_OUTDIR}/Interval.cs
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenSolidExtensions.cs
)

# Build .NET DLL
add_custom_target(
    OpenSolidDotNet ALL
    ${CSHARP_COMPILER} /target:library /out:OpenSolid.dll ${CSHARP_SOURCE_FILES}
    WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
    DEPENDS OpenSolidPInvoke OpenSolidExtensions.cs
)
add_dependencies(OpenSolidDotNet OpenSolidPInvoke)
