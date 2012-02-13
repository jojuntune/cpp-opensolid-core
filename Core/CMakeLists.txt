########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    
########## Set up Protocol Buffers serialization ##########

    # Generate opensolid.pb.h, opensolid.pb.cc from message format definition in opensolid.proto
    ADD_CUSTOM_COMMAND(
        OUTPUT
        ${OpenSolid}/Core/opensolid.pb.h
        ${OpenSolid}/Core/opensolid.pb.cc
        DEPENDS
        protoc
        ${OpenSolid}/Core/opensolid.proto
        COMMAND
        protoc
        ARGS
        --proto_path=${OpenSolid}/Core
        --cpp_out=${OpenSolid}/Core
        ${OpenSolid}/Core/opensolid.proto
    )

########## Define lists of source files ##########

    # Core directory files
    SET(CORE_FILES
        ${OpenSolid}/Core/config.hpp
        ${OpenSolid}/Core/opensolid.proto
        ${OpenSolid}/Core/Template.cpp
        ${OpenSolid}/Core/Template.hpp
        ${OpenSolid}/Core/TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        ${OpenSolid}/Core/Common/Bounds.hpp
        ${OpenSolid}/Core/Common/BoundsTests.hpp
        ${OpenSolid}/Core/Common/Convertible.hpp
        ${OpenSolid}/Core/Common/Error.hpp
        ${OpenSolid}/Core/Common/Evaluation.hpp
        ${OpenSolid}/Core/Common/Hash.hpp
        ${OpenSolid}/Core/Common/MatrixArgument.hpp
        ${OpenSolid}/Core/Common/ReferenceCounted.hpp
        ${OpenSolid}/Core/Common/Serialization.hpp
        ${OpenSolid}/Core/Common/Transformable.hpp
    )
    SET(COMMON_SOURCES
    )
    
    # Datum directory files
    SET(DATUM_HEADERS
        ${OpenSolid}/Core/Datum/Axis.hpp
        ${OpenSolid}/Core/Datum/Datum.hpp
        ${OpenSolid}/Core/Datum/DatumTests.hpp
        ${OpenSolid}/Core/Datum/Frame.hpp
        ${OpenSolid}/Core/Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
        ${OpenSolid}/Core/Datum/Axis.cpp
        ${OpenSolid}/Core/Datum/Datum.cpp
        ${OpenSolid}/Core/Datum/Frame.cpp
        ${OpenSolid}/Core/Datum/Plane.cpp
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS
        ${OpenSolid}/Core/Domain/Domain.hpp
        ${OpenSolid}/Core/Domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        ${OpenSolid}/Core/Domain/Domain.cpp
        ${OpenSolid}/Core/Domain/DomainConstructors.cpp
    )

    # Domain/DomainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        ${OpenSolid}/Core/Domain/DomainImplementation/DomainImplementation.hpp
        ${OpenSolid}/Core/Domain/DomainImplementation/GenericDomain.hpp
        ${OpenSolid}/Core/Domain/DomainImplementation/IntervalDomain.hpp
        ${OpenSolid}/Core/Domain/DomainImplementation/RectangleDomain.hpp
        ${OpenSolid}/Core/Domain/DomainImplementation/CuboidDomain.hpp
        ${OpenSolid}/Core/Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        ${OpenSolid}/Core/Domain/DomainImplementation/DomainImplementation.cpp
        ${OpenSolid}/Core/Domain/DomainImplementation/GenericDomain.cpp
        ${OpenSolid}/Core/Domain/DomainImplementation/IntervalDomain.cpp
        ${OpenSolid}/Core/Domain/DomainImplementation/RectangleDomain.cpp
        ${OpenSolid}/Core/Domain/DomainImplementation/CuboidDomain.cpp
        ${OpenSolid}/Core/Domain/DomainImplementation/SimplexDomain.cpp
    )
    
    # Function directory files
    SET(FUNCTION_HEADERS
        ${OpenSolid}/Core/Function/Function.hpp
        ${OpenSolid}/Core/Function/FunctionConstructors.hpp
        ${OpenSolid}/Core/Function/FunctionTests.hpp
        ${OpenSolid}/Core/Function/FunctionResult.hpp
    )
    SET(FUNCTION_SOURCES
        ${OpenSolid}/Core/Function/Function.cpp
        ${OpenSolid}/Core/Function/FunctionConstructors.cpp
    )
    
    # Function/FunctionImplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        ${OpenSolid}/Core/Function/FunctionImplementation/ArccosineFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ArcsineFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/BinaryOperation.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ComponentsFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CompositionFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ConcatenationFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ConstantFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CosineFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CrossProductFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/DifferenceFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/DotProductFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/EllipticalFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ExponentialFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/FunctionImplementation.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/LinearFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/LogarithmFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NegationFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NormalizedFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NormFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ParametersFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/PowerFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ProductFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/QuotientFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SineFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SquaredNormFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SquareRootFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SumFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/TangentFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/TransformedFunction.hpp
        ${OpenSolid}/Core/Function/FunctionImplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        ${OpenSolid}/Core/Function/FunctionImplementation/ArccosineFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ArcsineFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/BinaryOperation.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ComponentsFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CompositionFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ConcatenationFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ConstantFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CosineFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/CrossProductFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/DifferenceFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/DotProductFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/EllipticalFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ExponentialFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/FunctionImplementation.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/LinearFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/LogarithmFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NegationFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NormalizedFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/NormFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ParametersFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/PowerFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/ProductFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/QuotientFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SineFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SquaredNormFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SquareRootFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/SumFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/TangentFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/TransformedFunction.cpp
        ${OpenSolid}/Core/Function/FunctionImplementation/UnaryOperation.cpp
    )
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        ${OpenSolid}/Core/Geometry/Geometry.hpp
        ${OpenSolid}/Core/Geometry/GeometryConstructors.hpp
        ${OpenSolid}/Core/Geometry/GeometryResult.hpp
        ${OpenSolid}/Core/Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        ${OpenSolid}/Core/Geometry/Geometry.cpp
        ${OpenSolid}/Core/Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        ${OpenSolid}/Core/Geometry/GeometryImplementation/ConstantGeometry.hpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/GenericGeometry.hpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/GeometryImplementation.hpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        ${OpenSolid}/Core/Geometry/GeometryImplementation/ConstantGeometry.cpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/GenericGeometry.cpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/GeometryImplementation.cpp
        ${OpenSolid}/Core/Geometry/GeometryImplementation/SimplexGeometry.cpp
    )
    
    # Matrix directory files
    SET(MATRIX_HEADERS
        ${OpenSolid}/Core/Matrix/DenseBasePlugin.hpp
        ${OpenSolid}/Core/Matrix/Matrix.hpp
        ${OpenSolid}/Core/Matrix/MatrixBasePlugin.hpp
        ${OpenSolid}/Core/Matrix/MatrixTests.hpp
        ${OpenSolid}/Core/Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES)

    # Object directory files
    SET(OBJECT_HEADERS
        ${OpenSolid}/Core/Object/Object.hpp
        ${OpenSolid}/Core/Object/ObjectTests.hpp
    )
    SET(OBJECT_SOURCES
        ${OpenSolid}/Core/Object/Object.cpp
    )
    
    # Scalar directory files
    SET(SCALAR_HEADERS
        ${OpenSolid}/Core/Scalar/Comparison.hpp
        ${OpenSolid}/Core/Scalar/int.hpp
        ${OpenSolid}/Core/Scalar/double.hpp
        ${OpenSolid}/Core/Scalar/Interval.hpp
        ${OpenSolid}/Core/Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        ${OpenSolid}/Core/Scalar/Interval.cpp
    )
    
    # Set directory files
    SET(SET_HEADERS
        ${OpenSolid}/Core/Set/Set.hpp
        ${OpenSolid}/Core/Set/SetNode.hpp
        ${OpenSolid}/Core/Set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS
        ${OpenSolid}/Core/Simplex/Simplex.hpp
        ${OpenSolid}/Core/Simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        ${OpenSolid}/Core/Simplex/Simplex.cpp
    )

    # Support directory files
    SET(SUPPORT_HEADERS
        ${OpenSolid}/Core/Support/declarations.hpp
        ${OpenSolid}/Core/Support/Boost.hpp
        ${OpenSolid}/Core/Support/STL.hpp
    )
    SET(SUPPORT_SOURCES
    )
    
    # Update global source list
    SET(GLOBAL_SOURCE_LIST ${GLOBAL_SOURCE_LIST}
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
        PARENT_SCOPE
    )
    
########## Set up source groups for Visual Studio ##########
    
    # SOURCE_GROUP(OpenSolid\\Core FILES ${CORE_FILES})
    # SOURCE_GROUP(OpenSolid\\Core\\Common FILES ${COMMON_HEADERS} ${COMMON_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Datum FILES ${DATUM_HEADERS} ${DATUM_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Domain FILES ${DOMAIN_HEADERS} ${DOMAIN_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Domain\\DomainImplementation FILES ${DOMAINIMPLEMENTATION_HEADERS} ${DOMAINIMPLEMENTATION_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Function\\FunctionImplementation FILES ${FUNCTIONIMPLEMENTATION_HEADERS} ${FUNCTIONIMPLEMENTATION_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Geometry\\GeometryImplementation FILES ${GEOMETRYIMPLEMENTATION_HEADERS} ${GEOMETRYIMPLEMENTATION_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Object FILES ${OBJECT_HEADERS} ${OBJECT_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Set FILES ${SET_HEADERS} ${SET_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Simplex FILES ${SIMPLEX_HEADERS} ${SIMPLEX_SOURCES})
    # SOURCE_GROUP(OpenSolid\\Core\\Support FILES ${SUPPORT_HEADERS} ${SUPPORT_SOURCES})
    
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
        ${OpenSolid}/Core/opensolid.pb.cc
    )

    TARGET_LINK_LIBRARIES(OpenSolidCore libprotobuf)
    
########## Compile tests ##########

    ADD_CXXTEST(IntervalTests ${OpenSolid}/Core/Scalar/IntervalTests.hpp OpenSolidCore)
    ADD_CXXTEST(MatrixTests ${OpenSolid}/Core/Matrix/MatrixTests.hpp OpenSolidCore)
    ADD_CXXTEST(DatumTests ${OpenSolid}/Core/Datum/DatumTests.hpp OpenSolidCore)
    ADD_CXXTEST(SetTests ${OpenSolid}/Core/Set/SetTests.hpp OpenSolidCore)
    ADD_CXXTEST(FunctionTests ${OpenSolid}/Core/Function/FunctionTests.hpp OpenSolidCore)
    ADD_CXXTEST(GeometryTests ${OpenSolid}/Core/Geometry/GeometryTests.hpp OpenSolidCore)
    ADD_CXXTEST(SimplexTests ${OpenSolid}/Core/Simplex/SimplexTests.hpp OpenSolidCore)
    ADD_CXXTEST(BoundsTests ${OpenSolid}/Core/Common/BoundsTests.hpp OpenSolidCore)
    ADD_CXXTEST(ObjectTests ${OpenSolid}/Core/Object/ObjectTests.hpp OpenSolidCore)
    
########## Install headers ##########
    
    INSTALL(DIRECTORY ${OpenSolid}/Core
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/OpenSolid
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
