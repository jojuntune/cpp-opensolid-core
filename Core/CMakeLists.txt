######################################################################
#                                                                    #
#                             CONFIGURE                              #
#                                                                    #
######################################################################

########## General setup ##########

    PROJECT(OpenSolidCore)
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
        SET(LIBRARY_OUTPUT_PATH ${OpenSolidCore_BINARY_DIR})
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolidCore_BINARY_DIR})
    ELSE (MSVC_IDE)
        SET(LIBRARY_OUTPUT_PATH ${OpenSolidCore_BINARY_DIR}/bin)
        SET(EXECUTABLE_OUTPUT_PATH ${OpenSolidCore_BINARY_DIR}/bin)
    ENDIF (MSVC_IDE)

    # Initialize local include paths
    INCLUDE_DIRECTORIES(BEFORE
        ${OpenSolidCore_SOURCE_DIR}/External
        ${OpenSolidCore_SOURCE_DIR}/../..
    )
    
########## Set up Python ##########

    FIND_PACKAGE(PythonInterp REQUIRED)

########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    
    # Add Boost library directory to link path so auto-linking works when using MSVC
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

########## Set up CxxTest ##########

    MACRO(ADD_CXXTEST name source)
        # Generate test source file
        ADD_CUSTOM_COMMAND(
            OUTPUT
            ${OpenSolidCore_BINARY_DIR}/${name}.cpp
            DEPENDS
            ${source}
            COMMAND
            ${PYTHON_EXECUTABLE}
            ARGS
            ${OpenSolidCore_SOURCE_DIR}/External/cxxtest/cxxtestgen.py
            --error-printer
            -o ${OpenSolidCore_BINARY_DIR}/${name}.cpp
            ${source}
        )

        # Create test executable
        ADD_EXECUTABLE(${name} ${OpenSolidCore_BINARY_DIR}/${name}.cpp)

        # Link test executable to any libraries specified as additional macro arguments
        TARGET_LINK_LIBRARIES(${name} ${ARGN})

        # Register executable as a test
        ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ENDMACRO(ADD_CXXTEST)
    
########## Set up Protocol Buffers ##########

    SET(LIBPROTOBUF_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/descriptor.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/descriptor.pb.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/descriptor_database.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/dynamic_message.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/extension_set.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/extension_set_heavy.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/generated_message_reflection.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/generated_message_util.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/message.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/message_lite.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/reflection_ops.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/repeated_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/service.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/text_format.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/unknown_field_set.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/wire_format.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/wire_format_lite.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/coded_stream.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/gzip_stream.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/printer.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/tokenizer.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream_impl.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/io/zero_copy_stream_impl_lite.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/stubs/common.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/stubs/once.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/stubs/structurally_valid.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/stubs/strutil.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/stubs/substitute.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/importer.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/parser.cc
    )

    SET(LIBPROTOC_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/code_generator.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/command_line_interface.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/plugin.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/plugin.pb.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/subprocess.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/zip_writer.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_enum.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_enum_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_extension.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_file.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_generator.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_helpers.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_message.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_message_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_primitive_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_service.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/cpp/cpp_string_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_enum.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_enum_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_extension.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_file.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_generator.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_helpers.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_message.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_message_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_primitive_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_service.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/java/java_string_field.cc
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/python/python_generator.cc
    )

    SET(PROTOC_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/External/google/protobuf/compiler/main.cc        
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
        ${OpenSolidCore_SOURCE_DIR}/opensolid.pb.h
        ${OpenSolidCore_SOURCE_DIR}/opensolid.pb.cc
        DEPENDS
        protoc
        ${OpenSolidCore_SOURCE_DIR}/opensolid.proto
        COMMAND
        protoc
        ARGS
        --proto_path=${OpenSolidCore_SOURCE_DIR}
        --cpp_out=${OpenSolidCore_SOURCE_DIR}
        ${OpenSolidCore_SOURCE_DIR}/opensolid.proto
    )

########## Define lists of source files ##########

    # Root directory files
    SET(CORE_FILES
        ${OpenSolidCore_SOURCE_DIR}/config.hpp
        ${OpenSolidCore_SOURCE_DIR}/opensolid.proto
        ${OpenSolidCore_SOURCE_DIR}/Template.cpp
        ${OpenSolidCore_SOURCE_DIR}/Template.hpp
        ${OpenSolidCore_SOURCE_DIR}/TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Common/Bounds.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/BoundsTests.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Convertible.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Error.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Evaluation.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Hash.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/MatrixArgument.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/ReferenceCounted.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Serialization.hpp
        ${OpenSolidCore_SOURCE_DIR}/Common/Transformable.hpp
    )
    SET(COMMON_SOURCES
    )
    
    # Datum directory files
    SET(DATUM_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Datum/Axis.hpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Datum.hpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/DatumTests.hpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Frame.hpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Datum/Axis.cpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Datum.cpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Frame.cpp
        ${OpenSolidCore_SOURCE_DIR}/Datum/Plane.cpp
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Domain/Domain.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Domain/Domain.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainConstructors.cpp
    )

    # Domain/DomainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.hpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/DomainImplementation.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/GenericDomain.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/IntervalDomain.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/RectangleDomain.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/CuboidDomain.cpp
        ${OpenSolidCore_SOURCE_DIR}/Domain/DomainImplementation/SimplexDomain.cpp
    )
    
    # Function directory files
    SET(FUNCTION_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Function/Function.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionConstructors.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionTests.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionResult.hpp
    )
    SET(FUNCTION_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Function/Function.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionConstructors.cpp
    )
    
    # Function/FunctionImplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.hpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ArccosineFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ArcsineFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/BinaryOperation.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ComponentsFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CompositionFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ConcatenationFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ConstantFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CosineFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/CrossProductFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/DifferenceFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/DotProductFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/EllipticalFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ExponentialFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/FunctionImplementation.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/LinearFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/LogarithmFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NegationFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NormalizedFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/NormFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ParametersFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/PowerFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/ProductFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/QuotientFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SineFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SquaredNormFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SquareRootFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/SumFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/TangentFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/TransformedFunction.cpp
        ${OpenSolidCore_SOURCE_DIR}/Function/FunctionImplementation/UnaryOperation.cpp
    )
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Geometry/Geometry.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryConstructors.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryResult.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Geometry/Geometry.cpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.hpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/ConstantGeometry.cpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/GenericGeometry.cpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/GeometryImplementation.cpp
        ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryImplementation/SimplexGeometry.cpp
    )
    
    # Matrix directory files
    SET(MATRIX_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Matrix/DenseBasePlugin.hpp
        ${OpenSolidCore_SOURCE_DIR}/Matrix/Matrix.hpp
        ${OpenSolidCore_SOURCE_DIR}/Matrix/MatrixBasePlugin.hpp
        ${OpenSolidCore_SOURCE_DIR}/Matrix/MatrixTests.hpp
        ${OpenSolidCore_SOURCE_DIR}/Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES)

    # Object directory files
    SET(OBJECT_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Object/Object.hpp
        ${OpenSolidCore_SOURCE_DIR}/Object/ObjectTests.hpp
    )
    SET(OBJECT_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Object/Object.cpp
    )
    
    # Scalar directory files
    SET(SCALAR_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Scalar/Comparison.hpp
        ${OpenSolidCore_SOURCE_DIR}/Scalar/int.hpp
        ${OpenSolidCore_SOURCE_DIR}/Scalar/double.hpp
        ${OpenSolidCore_SOURCE_DIR}/Scalar/Interval.hpp
        ${OpenSolidCore_SOURCE_DIR}/Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Scalar/Interval.cpp
    )
    
    # Set directory files
    SET(SET_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Set/Set.hpp
        ${OpenSolidCore_SOURCE_DIR}/Set/SetNode.hpp
        ${OpenSolidCore_SOURCE_DIR}/Set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Simplex/Simplex.hpp
        ${OpenSolidCore_SOURCE_DIR}/Simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        ${OpenSolidCore_SOURCE_DIR}/Simplex/Simplex.cpp
    )

    # Support directory files
    SET(SUPPORT_HEADERS
        ${OpenSolidCore_SOURCE_DIR}/Support/declarations.hpp
        ${OpenSolidCore_SOURCE_DIR}/Support/Boost.hpp
        ${OpenSolidCore_SOURCE_DIR}/Support/STL.hpp
    )
    SET(SUPPORT_SOURCES
    )
    
    # All header and source files
    SET(ALL_HEADERS_AND_SOURCES
        ${CORE_FILES}
        ${COMMON_HEADERS}
        ${COMMON_SOURCES}
        ${DATUM_HEADERS}
        ${DATUM_SOURCES}
        ${DOMAIN_HEADERS}
        ${DOMAIN_SOURCES}
        ${DOMAINIMPLEMENTATION_HEADERS}
        ${DOMAINIMPLEMENTATION_SOURCES}
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
        ${OBJECT_HEADERS}
        ${OBJECT_SOURCES}
        ${SCALAR_HEADERS}
        ${SCALAR_SOURCES}
        ${SET_HEADERS}
        ${SET_SOURCES}
        ${SIMPLEX_HEADERS}
        ${SIMPLEX_SOURCES}
        ${SUPPORT_HEADERS}
        ${SUPPORT_SOURCES}
    )
    
########## Set up source groups for Visual Studio ##########

    # Dummy library that is never built but provides a Visual Studio target that includes
    # a complete source tree
    ADD_LIBRARY(ALL_SOURCES EXCLUDE_FROM_ALL ${ALL_HEADERS_AND_SOURCES})
    
    SOURCE_GROUP(Core FILES ${CORE_FILES})
    SOURCE_GROUP(Core\\Common FILES ${COMMON_HEADERS} ${COMMON_SOURCES})
    SOURCE_GROUP(Core\\Datum FILES ${DATUM_HEADERS} ${DATUM_SOURCES})
    SOURCE_GROUP(Core\\Domain FILES ${DOMAIN_HEADERS} ${DOMAIN_SOURCES})
    SOURCE_GROUP(Core\\Domain\\DomainImplementation FILES ${DOMAINIMPLEMENTATION_HEADERS} ${DOMAINIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(Core\\Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    SOURCE_GROUP(Core\\Function\\FunctionImplementation FILES ${FUNCTIONIMPLEMENTATION_HEADERS} ${FUNCTIONIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(Core\\Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    SOURCE_GROUP(Core\\Geometry\\GeometryImplementation FILES ${GEOMETRYIMPLEMENTATION_HEADERS} ${GEOMETRYIMPLEMENTATION_SOURCES})
    SOURCE_GROUP(Core\\Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    SOURCE_GROUP(Core\\Object FILES ${OBJECT_HEADERS} ${OBJECT_SOURCES})
    SOURCE_GROUP(Core\\Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    SOURCE_GROUP(Core\\Set FILES ${SET_HEADERS} ${SET_SOURCES})
    SOURCE_GROUP(Core\\Simplex FILES ${SIMPLEX_HEADERS} ${SIMPLEX_SOURCES})
    SOURCE_GROUP(Core\\Support FILES ${SUPPORT_HEADERS} ${SUPPORT_SOURCES})
    
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
        ${OBJECT_SOURCES}
        ${SCALAR_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
        ${OpenSolidCore_SOURCE_DIR}/opensolid.pb.cc
    )

    TARGET_LINK_LIBRARIES(OpenSolidCore libprotobuf)
    
########## Compile tests ##########

    ADD_CXXTEST(IntervalTests ${OpenSolidCore_SOURCE_DIR}/Scalar/IntervalTests.hpp OpenSolidCore)
    ADD_CXXTEST(MatrixTests ${OpenSolidCore_SOURCE_DIR}/Matrix/MatrixTests.hpp OpenSolidCore)
    ADD_CXXTEST(DatumTests ${OpenSolidCore_SOURCE_DIR}/Datum/DatumTests.hpp OpenSolidCore)
    ADD_CXXTEST(SetTests ${OpenSolidCore_SOURCE_DIR}/Set/SetTests.hpp OpenSolidCore)
    ADD_CXXTEST(FunctionTests ${OpenSolidCore_SOURCE_DIR}/Function/FunctionTests.hpp OpenSolidCore)
    ADD_CXXTEST(GeometryTests ${OpenSolidCore_SOURCE_DIR}/Geometry/GeometryTests.hpp OpenSolidCore)
    ADD_CXXTEST(SimplexTests ${OpenSolidCore_SOURCE_DIR}/Simplex/SimplexTests.hpp OpenSolidCore)
    ADD_CXXTEST(BoundsTests ${OpenSolidCore_SOURCE_DIR}/Common/BoundsTests.hpp OpenSolidCore)
    ADD_CXXTEST(ObjectTests ${OpenSolidCore_SOURCE_DIR}/Object/ObjectTests.hpp OpenSolidCore)
    
######################################################################
#                                                                    #
#                              INSTALL                               #
#                                                                    #
######################################################################
    
########## Install headers ##########
    
    INSTALL(DIRECTORY ${OpenSolidCore_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/OpenSolid/Core
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.h"
        PATTERN "Eigen/*"
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN "*Tests.hpp" EXCLUDE
        PATTERN "Template.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    INSTALL(TARGETS OpenSolidCore
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
