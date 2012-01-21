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
    INCLUDE_DIRECTORIES(BEFORE ../External ..)
    
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
            ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
            DEPENDS
            ${source}
            COMMAND
            ${PYTHON_EXECUTABLE}
            ARGS
            ${OpenSolid_SOURCE_DIR}/../External/cxxtest/cxxtestgen.py
            --error-printer
            -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/${source}
        )

        # Create test executable
        ADD_EXECUTABLE(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}.cpp)

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ENDMACRO(ADD_CXXTEST)
    
########## Set up Protocol Buffers ##########

    SET(LIBPROTOBUF_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/descriptor.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/descriptor.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/descriptor_database.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/dynamic_message.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/extension_set.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/extension_set_heavy.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/generated_message_reflection.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/generated_message_util.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/message.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/message_lite.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/reflection_ops.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/repeated_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/service.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/text_format.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/unknown_field_set.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/wire_format.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/wire_format_lite.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/coded_stream.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/gzip_stream.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/printer.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/tokenizer.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/zero_copy_stream.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/zero_copy_stream_impl.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/io/zero_copy_stream_impl_lite.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/stubs/common.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/stubs/once.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/stubs/structurally_valid.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/stubs/strutil.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/stubs/substitute.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/importer.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/parser.cc
    )

    SET(LIBPROTOC_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/code_generator.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/command_line_interface.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/plugin.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/plugin.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/subprocess.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/zip_writer.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_enum.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_enum_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_extension.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_file.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_generator.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_helpers.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_message.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_message_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_primitive_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_service.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/cpp/cpp_string_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_enum.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_enum_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_extension.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_file.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_generator.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_helpers.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_message.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_message_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_primitive_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_service.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/java/java_string_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/python/python_generator.cc
    )

    SET(PROTOC_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../External/google/protobuf/compiler/main.cc        
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
        ${CMAKE_CURRENT_BINARY_DIR}/opensolid.pb.h
        ${CMAKE_CURRENT_BINARY_DIR}/opensolid.pb.cc
        DEPENDS
        protoc
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialized/opensolid.proto
        COMMAND
        protoc
        ARGS
        --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/Serialized
        --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialized/opensolid.proto
    )
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

########## Define lists of source files ##########

    # OpenSolid directory files
    SET(OPENSOLID_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/bindTemplate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Template.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Template.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Bounds.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/BoundsTests.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Convertible.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Error.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Evaluation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Hash.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/MatrixArgument.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/ReferenceCounted.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Repr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Transformable.hpp
    )
    SET(COMMON_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Error.cpp
    )
    
    # Datum directory files
    SET(DATUM_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Datum/Axis.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Datum/Datum.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Datum/DatumTests.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Datum/Frame.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/Domain.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/Domain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainConstructors.cpp
    )

    # Domain/DomainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.cpp
    )
    
    # Function directory files
    SET(FUNCTION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/Function.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionConstructors.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionTests.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionResult.hpp
    )
    SET(FUNCTION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/Function.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionConstructors.cpp
    )
    
    # Function/FunctionImplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.cpp
    )
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Geometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryConstructors.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryResult.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Geometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.cpp
    )
    
    # Matrix directory files
    SET(MATRIX_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Matrix/DenseBasePlugin.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Matrix/Matrix.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Matrix/MatrixBasePlugin.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Matrix/MatrixTests.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES)

    # Model directory files
    SET(MODEL_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Model/Model.hpp
    )
    SET(MODEL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Model/Model.cpp
    )

    # Object directory files
    SET(OBJECT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Object/Object.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Object/ObjectTests.hpp
    )
    SET(OBJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Object/Object.cpp
    )
    
    # Python directory files
    SET(PYTHON_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/check.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/PythonEnvironment.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/PythonModule.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/PythonTests.hpp
    )
    SET(PYTHON_MODULE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindComparison.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindDatum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindDouble.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindInterval.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindMatrixConstructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/bindSimplex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/check.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/PythonModule.cpp
    )
    SET(PYTHON_ENVIRONMENT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Python/PythonEnvironment.cpp
    )

    # Scalar directory files
    SET(SCALAR_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/Comparison.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/int.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/double.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/Interval.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Scalar/Interval.cpp
    )
    
    # Serialized directory files
    SET(SERIALIZED_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialized/opensolid.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialized/Interval.hpp
    )
    SET(SERIALIZED_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialized/Interval.cpp
    )
    
    # Set directory files
    SET(SET_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Set/Set.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Set/SetNode.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Simplex/Simplex.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Simplex/Simplex.cpp
    )

    # Support directory files
    SET(SUPPORT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Support/declarations.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Support/Boost.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Support/STL.hpp
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
        ${SERIALIZED_HEADERS}
        ${SERIALIZED_SOURCES}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/checker.py
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
    SOURCE_GROUP(OpenSolid\\Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Function\\FunctionImplementation FILES ${FUNCTIONIMPLEMENTATION_HEADERS} ${FUNCTIONIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry\\GeometryImplementation FILES ${GEOMETRYIMPLEMENTATION_HEADERS} ${GEOMETRYIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    SOURCE_GROUP(OpenSolid\\Model FILES ${MODEL_HEADERS} ${MODEL_SOURCES})
    SOURCE_GROUP(OpenSolid\\Object FILES ${OBJECT_HEADERS} ${OBJECT_SOURCES})
    SOURCE_GROUP(OpenSolid\\Python FILES ${PYTHON_HEADERS} ${PYTHON_MODULE_SOURCES} ${PYTHON_ENVIRONMENT_SOURCES})
    SOURCE_GROUP(OpenSolid\\Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    SOURCE_GROUP(OpenSolid\\Serialized FILES ${SERIALIZED_HEADERS} ${SERIALIZED_SOURCES})
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
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_SOURCES}
        ${MODEL_SOURCES}
        ${OBJECT_SOURCES}
        ${PRIMITIVE_SOURCES}
        ${SCALAR_SOURCES}
        ${SERIALIZED_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
        ${CMAKE_CURRENT_BINARY_DIR}/opensolid.pb.cc
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

    ADD_CXXTEST(IntervalTests Scalar/IntervalTests.hpp OpenSolidCore)
    ADD_CXXTEST(MatrixTests Matrix/MatrixTests.hpp OpenSolidCore)
    ADD_CXXTEST(DatumTests Datum/DatumTests.hpp OpenSolidCore)
    ADD_CXXTEST(SetTests Set/SetTests.hpp OpenSolidCore)
    ADD_CXXTEST(FunctionTests Function/FunctionTests.hpp OpenSolidCore)
    ADD_CXXTEST(GeometryTests Geometry/GeometryTests.hpp OpenSolidCore)
    ADD_CXXTEST(SimplexTests Simplex/SimplexTests.hpp OpenSolidCore)
    ADD_CXXTEST(PythonTests Python/PythonTests.hpp OpenSolidPython OpenSolidCore)
    ADD_CXXTEST(BoundsTests Common/BoundsTests.hpp OpenSolidCore)
    ADD_CXXTEST(ObjectTests Object/ObjectTests.hpp OpenSolidCore)
    
######################################################################
#                                                                    #
#                              INSTALL                               #
#                                                                    #
######################################################################
    
########## Install Eigen headers ##########

    INSTALL(DIRECTORY ../External/Eigen
        DESTINATION include
        PATTERN "CMakeLists.txt" EXCLUDE
    )
    
########## Install OpenSolid headers ##########
    
    INSTALL(DIRECTORY ../OpenSolid
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN "*Tests.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    INSTALL(TARGETS OpenSolidCore OpenSolidPython opensolid
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )

    # Install Python extension module
    INSTALL(TARGETS opensolid DESTINATION ${PYTHON_SITE_PACKAGES})
