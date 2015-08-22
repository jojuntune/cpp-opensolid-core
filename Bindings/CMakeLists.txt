find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Set up SWIG
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
set(CMAKE_SWIG_FLAGS -c++)

# Set up interface file
set_property(SOURCE opensolid.i PROPERTY CPLUSPLUS ON)
set(
    CLASS_HEADERS
    JInterval.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${BUILD_DOTNET_BINDINGS})
    # Build P/Invoke DLL
    set(SWIG_MODULE_OpenSolidPInvoke_EXTRA_DEPS ${CLASS_HEADERS})
    set(SWIG_DOTNET_FLAGS -namespace OpenSolid -dllimport OpenSolidPInvoke)
    set_property(SOURCE opensolid.i PROPERTY SWIG_FLAGS ${SWIG_DOTNET_FLAGS})
    swig_add_module(OpenSolidPInvoke csharp opensolid.i)
    swig_link_libraries(OpenSolidPInvoke OpenSolidCore)

    # Collect C# source files to be compiled into OpenSolid .NET DLL
    set(
        CSHARP_SOURCE_FILES
        ${CMAKE_SWIG_OUTDIR}/OpenSolidPINVOKE.cs
        ${CMAKE_SWIG_OUTDIR}/OpenSolid.cs
        ${CMAKE_SWIG_OUTDIR}/Interval.cs
    )
    file(TO_NATIVE_PATH "${CSHARP_SOURCE_FILES}" CSHARP_SOURCE_FILES_NATIVE_PATHS)

    # Build .NET DLL
    add_custom_target(
        OpenSolidDotNet ALL
        ${CSHARP_COMPILER} /target:library /out:OpenSolid.dll ${CSHARP_SOURCE_FILES_NATIVE_PATHS}
        WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
        DEPENDS OpenSolidPInvoke
    )
    add_dependencies(OpenSolidDotNet OpenSolidPInvoke)
endif()

if(${BUILD_JAVA_BINDINGS})
    # Build JNI DLL
    set(SWIG_MODULE_OpenSolidJNI_EXTRA_DEPS ${CLASS_HEADERS})
    set(SWIG_JAVA_FLAGS -package org.opensolid)
    set_property(SOURCE opensolid.i PROPERTY SWIG_FLAGS ${SWIG_JAVA_FLAGS})
    include_directories(${JNI_INCLUDE_DIRS})
    swig_add_module(OpenSolidJNI java opensolid.i)
    swig_link_libraries(OpenSolidJNI OpenSolidCore)

    # Collect Java source files to be compiled into OpenSolid JAR
    set(
        JAVA_SOURCE_FILES
        ${CMAKE_SWIG_OUTDIR}/OpenSolidJNI.java
        ${CMAKE_SWIG_OUTDIR}/OpenSolid.java
        ${CMAKE_SWIG_OUTDIR}/Interval.java
    )
    add_jar(opensolid SOURCES ${JAVA_SOURCE_FILES})
    add_dependencies(opensolid OpenSolidJNI)
endif()
