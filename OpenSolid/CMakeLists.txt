######################################################################
#                                                                    #
#                             CONFIGURE                              #
#                                                                    #
######################################################################

########## General setup ##########

    PROJECT(OpenSolid)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
    ENABLE_TESTING()

    # Set up compiler-specific flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Enable C++0x and add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wno-unused-variable")
        SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG")
        # Enable -fPIC on 64-bit systems where it is required
        IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF (GCC_VERSION VERSION_LESS 4.6)
            ADD_DEFINITIONS(-Dnullptr=0)
        ENDIF (GCC_VERSION VERSION_LESS 4.6)
    ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
        # Use -pthread compilation option to properly link to threading library
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    ELSEIF (WIN32)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        ADD_DEFINITIONS(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)

        # Add /MP flag for parallel compilation within projects
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)

    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

    # Collect compiled binaries in single directory
    IF (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${OpenSolid_BINARY_DIR})
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolid_BINARY_DIR})
    ELSE (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${OpenSolid_BINARY_DIR}/bin)
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolid_BINARY_DIR}/bin)
    ENDIF (MSVC_IDE)

    # Initialize local include paths
    INCLUDE_DIRECTORIES(BEFORE
        ${OpenSolid_SOURCE_DIR}/External
        ${OpenSolid_SOURCE_DIR}/..
        ${OpenSolid_BINARY_DIR}/..
    )
    
########## Set up Python ##########

    FIND_PACKAGE(PythonInterp REQUIRED)
    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

    # Get site packages directory
    EXECUTE_PROCESS(
        COMMAND ${PYTHON_EXECUTABLE}
        -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED COMPONENTS python)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    
    # Add Boost library directory to link path so auto-linking works when using MSVC
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

########## Set up CxxTest ##########

    MACRO(ADD_CXXTEST name source)
        # Generate test source file
        ADD_CUSTOM_COMMAND(
            OUTPUT
            ${OpenSolid_BINARY_DIR}/${name}.cpp
            DEPENDS
            ${source}
            COMMAND
            ${PYTHON_EXECUTABLE}
            ARGS
            ${OpenSolid_SOURCE_DIR}/External/cxxtest/cxxtestgen.py
            --error-printer
            -o ${OpenSolid_BINARY_DIR}/${name}.cpp
            ${source}
        )

        # Create test executable
        ADD_EXECUTABLE(${name} ${OpenSolid_BINARY_DIR}/${name}.cpp)

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ENDMACRO(ADD_CXXTEST)
    
########## Set up Protocol Buffers ##########

    SET(LIBPROTOBUF_SOURCES
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/descriptor.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/descriptor.pb.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/descriptor_database.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/dynamic_message.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/extension_set.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/extension_set_heavy.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/generated_message_reflection.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/generated_message_util.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/message.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/message_lite.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/reflection_ops.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/repeated_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/service.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/text_format.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/unknown_field_set.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/wire_format.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/wire_format_lite.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/coded_stream.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/gzip_stream.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/printer.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/tokenizer.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream_impl.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream_impl_lite.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/stubs/common.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/stubs/once.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/stubs/structurally_valid.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/stubs/strutil.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/stubs/substitute.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/importer.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/parser.cc
    )

    SET(LIBPROTOC_SOURCES
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/code_generator.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/command_line_interface.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/plugin.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/plugin.pb.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/subprocess.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/zip_writer.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_enum.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_enum_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_extension.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_file.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_generator.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_helpers.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_message.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_message_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_primitive_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_service.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_string_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_enum.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_enum_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_extension.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_file.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_generator.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_helpers.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_message.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_message_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_primitive_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_service.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/java/java_string_field.cc
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/python/python_generator.cc
    )

    SET(PROTOC_SOURCES
        ${OpenSolid_SOURCE_DIR}/External/google/protobuf/compiler/main.cc        
    )
    
    # Compile static Protocol Buffers libraries
    ADD_LIBRARY(libprotobuf STATIC ${LIBPROTOBUF_SOURCES})
    ADD_LIBRARY(libprotoc STATIC ${LIBPROTOC_SOURCES})

    # Compile protoc, Protocol Buffers compiler executable
    ADD_EXECUTABLE(protoc ${PROTOC_SOURCES})
    TARGET_LINK_LIBRARIES(protoc libprotobuf libprotoc)

    # Disable warnings for Protocol Buffers compilation
    IF (CMAKE_COMPILER_IS_GNUCXX)
        SET_TARGET_PROPERTIES(libprotobuf libprotoc protoc PROPERTIES COMPILE_FLAGS "-w")
    ELSEIF(WIN32)
        SET_TARGET_PROPERTIES(libprotobuf libprotoc protoc PROPERTIES COMPILE_FLAGS "/W0")
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)

    # Generate opensolid.pb.h, opensolid.pb.cc from message format definition in opensolid.proto
    ADD_CUSTOM_COMMAND(
        OUTPUT
        ${OpenSolid_BINARY_DIR}/opensolid.pb.h
        ${OpenSolid_BINARY_DIR}/opensolid.pb.cc
        DEPENDS
        protoc
        ${OpenSolid_SOURCE_DIR}/opensolid.proto
        COMMAND
        protoc
        ARGS
        --proto_path=${OpenSolid_SOURCE_DIR}
        --cpp_out=${OpenSolid_BINARY_DIR}
        ${OpenSolid_SOURCE_DIR}/opensolid.proto
    )

########## Define lists of source files ##########

    # OpenSolid directory files
    SET(OPENSOLID_FILES
        ${OpenSolid_SOURCE_DIR}/bindTemplate.cpp
        ${OpenSolid_SOURCE_DIR}/config.hpp
        ${OpenSolid_SOURCE_DIR}/opensolid.proto
        ${OpenSolid_SOURCE_DIR}/Template.cpp
        ${OpenSolid_SOURCE_DIR}/Template.hpp
        ${OpenSolid_SOURCE_DIR}/TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        ${OpenSolid_SOURCE_DIR}/Common/Bounds.hpp
        ${OpenSolid_SOURCE_DIR}/Common/BoundsTests.hpp
        ${OpenSolid_SOURCE_DIR}/Common/Convertible.hpp
        ${OpenSolid_SOURCE_DIR}/Common/Evaluation.hpp
        ${OpenSolid_SOURCE_DIR}/Common/Hash.hpp
        ${OpenSolid_SOURCE_DIR}/Common/MatrixArgument.hpp
        ${OpenSolid_SOURCE_DIR}/Common/ReferenceCounted.hpp
        ${OpenSolid_SOURCE_DIR}/Common/Transformable.hpp
    )
    SET(COMMON_SOURCES
    )
    
    # Datum directory files
    SET(DATUM_HEADERS
        ${OpenSolid_SOURCE_DIR}/Datum/Axis.hpp
        ${OpenSolid_SOURCE_DIR}/Datum/Datum.hpp
        ${OpenSolid_SOURCE_DIR}/Datum/DatumTests.hpp
        ${OpenSolid_SOURCE_DIR}/Datum/Frame.hpp
        ${OpenSolid_SOURCE_DIR}/Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS
        ${OpenSolid_SOURCE_DIR}/Domain/Domain.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        ${OpenSolid_SOURCE_DIR}/Domain/Domain.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainConstructors.cpp
    )

    # Domain/DomainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.hpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.cpp
        ${OpenSolid_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.cpp
    )

    # Error directory files
    SET(ERROR_HEADERS
        ${OpenSolid_SOURCE_DIR}/Error/Error.hpp
    )
    SET(ERROR_SOURCES
        ${OpenSolid_SOURCE_DIR}/Error/Error.cpp
    )

    # Error/ErrorImplementation files
    SET(ERRORIMPLEMENTATION_HEADERS
        ${OpenSolid_SOURCE_DIR}/Error/ErrorImplementation/ErrorImplementation.hpp
    )
    SET(ERRORIMPLEMENTATION_SOURCES
        ${OpenSolid_SOURCE_DIR}/Error/ErrorImplementation/ErrorImplementation.cpp
    )
    
    # Function directory files
    SET(FUNCTION_HEADERS
        ${OpenSolid_SOURCE_DIR}/Function/Function.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionConstructors.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionTests.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionResult.hpp
    )
    SET(FUNCTION_SOURCES
        ${OpenSolid_SOURCE_DIR}/Function/Function.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionConstructors.cpp
    )
    
    # Function/FunctionImplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.hpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.cpp
    )
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        ${OpenSolid_SOURCE_DIR}/Geometry/Geometry.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryConstructors.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryResult.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        ${OpenSolid_SOURCE_DIR}/Geometry/Geometry.cpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.hpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.cpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.cpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.cpp
        ${OpenSolid_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.cpp
    )
    
    # Matrix directory files
    SET(MATRIX_HEADERS
        ${OpenSolid_SOURCE_DIR}/Matrix/DenseBasePlugin.hpp
        ${OpenSolid_SOURCE_DIR}/Matrix/Matrix.hpp
        ${OpenSolid_SOURCE_DIR}/Matrix/MatrixBasePlugin.hpp
        ${OpenSolid_SOURCE_DIR}/Matrix/MatrixTests.hpp
        ${OpenSolid_SOURCE_DIR}/Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES)

    # Model directory files
    SET(MODEL_HEADERS
        ${OpenSolid_SOURCE_DIR}/Model/Model.hpp
    )
    SET(MODEL_SOURCES
        ${OpenSolid_SOURCE_DIR}/Model/Model.cpp
    )

    # Object directory files
    SET(OBJECT_HEADERS
        ${OpenSolid_SOURCE_DIR}/Object/Object.hpp
        ${OpenSolid_SOURCE_DIR}/Object/ObjectTests.hpp
    )
    SET(OBJECT_SOURCES
        ${OpenSolid_SOURCE_DIR}/Object/Object.cpp
    )
    
    # Python directory files
    SET(PYTHON_HEADERS
        ${OpenSolid_SOURCE_DIR}/Python/PythonEnvironment.hpp
        ${OpenSolid_SOURCE_DIR}/Python/PythonModule.hpp
        ${OpenSolid_SOURCE_DIR}/Python/PythonTests.hpp
        ${OpenSolid_SOURCE_DIR}/Python/repr.hpp
    )
    SET(PYTHON_MODULE_SOURCES
        ${OpenSolid_SOURCE_DIR}/Python/bindComparison.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindDatum.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindFunction.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindDouble.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindInterval.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindMatrix.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindMatrixConstructors.cpp
        ${OpenSolid_SOURCE_DIR}/Python/bindSimplex.cpp
        ${OpenSolid_SOURCE_DIR}/Python/PythonModule.cpp
        ${OpenSolid_SOURCE_DIR}/Python/repr.cpp
    )
    SET(PYTHON_ENVIRONMENT_SOURCES
        ${OpenSolid_SOURCE_DIR}/Python/PythonEnvironment.cpp
    )

    # Scalar directory files
    SET(SCALAR_HEADERS
        ${OpenSolid_SOURCE_DIR}/Scalar/Comparison.hpp
        ${OpenSolid_SOURCE_DIR}/Scalar/int.hpp
        ${OpenSolid_SOURCE_DIR}/Scalar/double.hpp
        ${OpenSolid_SOURCE_DIR}/Scalar/Interval.hpp
        ${OpenSolid_SOURCE_DIR}/Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        ${OpenSolid_SOURCE_DIR}/Scalar/Interval.cpp
    )
    
    # Set directory files
    SET(SET_HEADERS
        ${OpenSolid_SOURCE_DIR}/Set/Set.hpp
        ${OpenSolid_SOURCE_DIR}/Set/SetNode.hpp
        ${OpenSolid_SOURCE_DIR}/Set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS
        ${OpenSolid_SOURCE_DIR}/Simplex/Simplex.hpp
        ${OpenSolid_SOURCE_DIR}/Simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        ${OpenSolid_SOURCE_DIR}/Simplex/Simplex.cpp
    )

    # Support directory files
    SET(SUPPORT_HEADERS
        ${OpenSolid_SOURCE_DIR}/Support/declarations.hpp
        ${OpenSolid_SOURCE_DIR}/Support/Boost.hpp
        ${OpenSolid_SOURCE_DIR}/Support/STL.hpp
    )
    SET(SUPPORT_SOURCES
    )
    
    # All header and source files
    SET(ALL_HEADERS_AND_SOURCES
        ${OPENSOLID_FILES}
        ${COMMON_HEADERS}
        ${COMMON_SOURCES}
        ${DATUM_HEADERS}
        ${DATUM_SOURCES}
        ${DOMAIN_HEADERS}
        ${DOMAIN_SOURCES}
        ${DOMAINIMPLEMENTATION_HEADERS}
        ${DOMAINIMPLEMENTATION_SOURCES}
        ${ERROR_HEADERS}
        ${ERROR_SOURCES}
        ${ERRORIMPLEMENTATION_HEADERS}
        ${ERRORIMPLEMENTATION_SOURCES}
        ${FUNCTION_HEADERS}
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_HEADERS}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_HEADERS}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_HEADERS}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_HEADERS}
        ${MATRIX_SOURCES}
        ${MODEL_HEADERS}
        ${MODEL_SOURCES}
        ${OBJECT_HEADERS}
        ${OBJECT_SOURCES}
        ${PYTHON_HEADERS}
        ${PYTHON_MODULE_SOURCES}
        ${PYTHON_ENVIRONMENT_SOURCES}
        ${SCALAR_HEADERS}
        ${SCALAR_SOURCES}
        ${SET_HEADERS}
        ${SET_SOURCES}
        ${SIMPLEX_HEADERS}
        ${SIMPLEX_SOURCES}
        ${SUPPORT_HEADERS}
        ${SUPPORT_SOURCES}
    )
    
########## Run source file checker ##########

    ADD_TEST(
        SourceChecks
        ${PYTHON_EXECUTABLE}
        ${OpenSolid_SOURCE_DIR}/checker.py
        ${ALL_HEADERS_AND_SOURCES}
    )
    
########## Set up source groups for Visual Studio ##########

    # Dummy library that is never built but provides a Visual Studio target that includes
    # a complete source tree
    ADD_LIBRARY(ALL_SOURCES EXCLUDE_FROM_ALL ${ALL_HEADERS_AND_SOURCES})
    
    SOURCE_GROUP(OpenSolid FILES ${OPENSOLID_FILES})
    SOURCE_GROUP(OpenSolid\\Common FILES ${COMMON_HEADERS} ${COMMON_SOURCES})
    SOURCE_GROUP(OpenSolid\\Datum FILES ${DATUM_HEADERS} ${DATUM_SOURCES})
    SOURCE_GROUP(OpenSolid\\Domain FILES ${DOMAIN_HEADERS} ${DOMAIN_SOURCES})
    SOURCE_GROUP(OpenSolid\\Domain\\DomainImplementation FILES ${DOMAINIMPLEMENTATION_HEADERS} ${DOMAINIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Error FILES ${ERROR_HEADERS} ${ERROR_SOURCES})
    SOURCE_GROUP(OpenSolid\\Error\\ErrorImplementation FILES ${ERRORIMPLEMENTATION_HEADERS} ${ERRORIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Function\\FunctionImplementation FILES ${FUNCTIONIMPLEMENTATION_HEADERS} ${FUNCTIONIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry\\GeometryImplementation FILES ${GEOMETRYIMPLEMENTATION_HEADERS} ${GEOMETRYIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    SOURCE_GROUP(OpenSolid\\Model FILES ${MODEL_HEADERS} ${MODEL_SOURCES})
    SOURCE_GROUP(OpenSolid\\Object FILES ${OBJECT_HEADERS} ${OBJECT_SOURCES})
    SOURCE_GROUP(OpenSolid\\Python FILES ${PYTHON_HEADERS} ${PYTHON_MODULE_SOURCES} ${PYTHON_ENVIRONMENT_SOURCES})
    SOURCE_GROUP(OpenSolid\\Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    SOURCE_GROUP(OpenSolid\\Set FILES ${SET_HEADERS} ${SET_SOURCES})
    SOURCE_GROUP(OpenSolid\\Simplex FILES ${SIMPLEX_HEADERS} ${SIMPLEX_SOURCES})
    SOURCE_GROUP(OpenSolid\\Support FILES ${SUPPORT_HEADERS} ${SUPPORT_SOURCES})
    
######################################################################
#                                                                    #
#                               BUILD                                #
#                                                                    #
######################################################################
    
########## Compile OpenSolidCore library ##########

    ADD_LIBRARY(OpenSolidCore SHARED
        ${COMMON_SOURCES}
        ${DATUM_SOURCES}
        ${DOMAIN_SOURCES}
        ${DOMAINIMPLEMENTATION_SOURCES}
        ${ERROR_SOURCES}
        ${ERRORIMPLEMENTATION_SOURCES}
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_SOURCES}
        ${MODEL_SOURCES}
        ${OBJECT_SOURCES}
        ${PRIMITIVE_SOURCES}
        ${SCALAR_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
        ${OpenSolid_BINARY_DIR}/opensolid.pb.cc
    )

    TARGET_LINK_LIBRARIES(OpenSolidCore libprotobuf)
    
########## Compile Python extension module ##########
    
    ADD_LIBRARY(opensolid SHARED ${PYTHON_MODULE_SOURCES})
    SET_TARGET_PROPERTIES(opensolid PROPERTIES PREFIX "")
    IF(WIN32)
        SET_TARGET_PROPERTIES(opensolid PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32)
    TARGET_LINK_LIBRARIES(opensolid OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
########## Compile OpenSolidPython library ##########
    
    ADD_LIBRARY(OpenSolidPython SHARED ${PYTHON_ENVIRONMENT_SOURCES})
    TARGET_LINK_LIBRARIES(OpenSolidPython
        OpenSolidCore
        opensolid
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile tests ##########

    ADD_CXXTEST(IntervalTests ${OpenSolid_SOURCE_DIR}/Scalar/IntervalTests.hpp OpenSolidCore)
    ADD_CXXTEST(MatrixTests ${OpenSolid_SOURCE_DIR}/Matrix/MatrixTests.hpp OpenSolidCore)
    ADD_CXXTEST(DatumTests ${OpenSolid_SOURCE_DIR}/Datum/DatumTests.hpp OpenSolidCore)
    ADD_CXXTEST(SetTests ${OpenSolid_SOURCE_DIR}/Set/SetTests.hpp OpenSolidCore)
    ADD_CXXTEST(FunctionTests ${OpenSolid_SOURCE_DIR}/Function/FunctionTests.hpp OpenSolidCore)
    ADD_CXXTEST(GeometryTests ${OpenSolid_SOURCE_DIR}/Geometry/GeometryTests.hpp OpenSolidCore)
    ADD_CXXTEST(SimplexTests ${OpenSolid_SOURCE_DIR}/Simplex/SimplexTests.hpp OpenSolidCore)
    ADD_CXXTEST(PythonTests ${OpenSolid_SOURCE_DIR}/Python/PythonTests.hpp OpenSolidPython OpenSolidCore)
    ADD_CXXTEST(BoundsTests ${OpenSolid_SOURCE_DIR}/Common/BoundsTests.hpp OpenSolidCore)
    ADD_CXXTEST(ObjectTests ${OpenSolid_SOURCE_DIR}/Object/ObjectTests.hpp OpenSolidCore)
    
######################################################################
#                                                                    #
#                              INSTALL                               #
#                                                                    #
######################################################################
    
########## Install headers ##########
    
    INSTALL(DIRECTORY ${OpenSolid_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.h"
        PATTERN "Eigen/*"
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN "*Tests.hpp" EXCLUDE
        PATTERN "Template.hpp" EXCLUDE
    )

    INSTALL(FILES ${OpenSolid_BINARY_DIR}/opensolid.pb.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/OpenSolid
    )
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    INSTALL(TARGETS OpenSolidCore OpenSolidPython opensolid
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

    # Install Python extension module
    INSTALL(TARGETS opensolid DESTINATION ${PYTHON_SITE_PACKAGES})
