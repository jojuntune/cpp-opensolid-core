########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

########## Define lists of source files ##########

    # Core directory files
    SET(CORE_FILES
        CMakeLists.txt
        config.hpp
        Template.cpp
        Template.hpp
        TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        Common/Error.hpp
        Common/Evaluation.hpp
        Common/List.hpp
        Common/Message.hpp
        Common/TypeDescription.hpp
        Common/Value.hpp
    )
    SET(COMMON_SOURCES
        Common/Error.cpp
        Common/List.cpp
        Common/Message.cpp
        Common/TypeDescription.cpp
        Common/Value.cpp
    )

    # Database directory files
    SET(DATABASE_HEADERS
        Database/Database.hpp
        Database/DatabaseTests.hpp
    )
    SET(DATABASE_SOURCES
        Database/Database.cpp
    )
    
    # Datum directory files
    SET(DATUM_HEADERS
        Datum/Axis.hpp
        Datum/Datum.hpp
        Datum/DatumTests.hpp
        Datum/Frame.hpp
        Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
        Datum/Axis.cpp
        Datum/Datum.cpp
        Datum/Frame.cpp
        Datum/Plane.cpp
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS
        Domain/Domain.hpp
        Domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        Domain/Domain.cpp
        Domain/DomainConstructors.cpp
    )

    # Domain/DomainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        Domain/DomainImplementation/DomainImplementation.hpp
        Domain/DomainImplementation/GenericDomain.hpp
        Domain/DomainImplementation/IntervalDomain.hpp
        Domain/DomainImplementation/RectangleDomain.hpp
        Domain/DomainImplementation/CuboidDomain.hpp
        Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        Domain/DomainImplementation/DomainImplementation.cpp
        Domain/DomainImplementation/GenericDomain.cpp
        Domain/DomainImplementation/IntervalDomain.cpp
        Domain/DomainImplementation/RectangleDomain.cpp
        Domain/DomainImplementation/CuboidDomain.cpp
        Domain/DomainImplementation/SimplexDomain.cpp
    )
    
    # Function directory files
    SET(FUNCTION_HEADERS
        Function/Function.hpp
        Function/FunctionConstructors.hpp
        Function/FunctionTests.hpp
    )
    SET(FUNCTION_SOURCES
        Function/Function.cpp
        Function/FunctionConstructors.cpp
    )
    
    # Function/FunctionImplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        Function/FunctionImplementation/ArccosineFunction.hpp
        Function/FunctionImplementation/ArcsineFunction.hpp
        Function/FunctionImplementation/BinaryOperation.hpp
        Function/FunctionImplementation/ComponentsFunction.hpp
        Function/FunctionImplementation/CompositionFunction.hpp
        Function/FunctionImplementation/ConcatenationFunction.hpp
        Function/FunctionImplementation/ConstantFunction.hpp
        Function/FunctionImplementation/CosineFunction.hpp
        Function/FunctionImplementation/CrossProductFunction.hpp
        Function/FunctionImplementation/DifferenceFunction.hpp
        Function/FunctionImplementation/DotProductFunction.hpp
        Function/FunctionImplementation/EllipticalFunction.hpp
        Function/FunctionImplementation/ExponentialFunction.hpp
        Function/FunctionImplementation/FunctionImplementation.hpp
        Function/FunctionImplementation/LinearFunction.hpp
        Function/FunctionImplementation/LogarithmFunction.hpp
        Function/FunctionImplementation/NegationFunction.hpp
        Function/FunctionImplementation/NormalizedFunction.hpp
        Function/FunctionImplementation/NormFunction.hpp
        Function/FunctionImplementation/ParametersFunction.hpp
        Function/FunctionImplementation/PowerFunction.hpp
        Function/FunctionImplementation/ProductFunction.hpp
        Function/FunctionImplementation/QuotientFunction.hpp
        Function/FunctionImplementation/SineFunction.hpp
        Function/FunctionImplementation/SquaredNormFunction.hpp
        Function/FunctionImplementation/SquareRootFunction.hpp
        Function/FunctionImplementation/SumFunction.hpp
        Function/FunctionImplementation/TangentFunction.hpp
        Function/FunctionImplementation/TransformedFunction.hpp
        Function/FunctionImplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        Function/FunctionImplementation/ArccosineFunction.cpp
        Function/FunctionImplementation/ArcsineFunction.cpp
        Function/FunctionImplementation/BinaryOperation.cpp
        Function/FunctionImplementation/ComponentsFunction.cpp
        Function/FunctionImplementation/CompositionFunction.cpp
        Function/FunctionImplementation/ConcatenationFunction.cpp
        Function/FunctionImplementation/ConstantFunction.cpp
        Function/FunctionImplementation/CosineFunction.cpp
        Function/FunctionImplementation/CrossProductFunction.cpp
        Function/FunctionImplementation/DifferenceFunction.cpp
        Function/FunctionImplementation/DotProductFunction.cpp
        Function/FunctionImplementation/EllipticalFunction.cpp
        Function/FunctionImplementation/ExponentialFunction.cpp
        Function/FunctionImplementation/FunctionImplementation.cpp
        Function/FunctionImplementation/LinearFunction.cpp
        Function/FunctionImplementation/LogarithmFunction.cpp
        Function/FunctionImplementation/NegationFunction.cpp
        Function/FunctionImplementation/NormalizedFunction.cpp
        Function/FunctionImplementation/NormFunction.cpp
        Function/FunctionImplementation/ParametersFunction.cpp
        Function/FunctionImplementation/PowerFunction.cpp
        Function/FunctionImplementation/ProductFunction.cpp
        Function/FunctionImplementation/QuotientFunction.cpp
        Function/FunctionImplementation/SineFunction.cpp
        Function/FunctionImplementation/SquaredNormFunction.cpp
        Function/FunctionImplementation/SquareRootFunction.cpp
        Function/FunctionImplementation/SumFunction.cpp
        Function/FunctionImplementation/TangentFunction.cpp
        Function/FunctionImplementation/TransformedFunction.cpp
        Function/FunctionImplementation/UnaryOperation.cpp
    )

    # Generic directory files
    SET(GENERIC_HEADERS
        Generic/Bounds.hpp
        Generic/Conversion.hpp
        Generic/ReferenceCounted.hpp
        Generic/TypeDescriptionFunction.hpp
        Generic/Transformable.hpp
        Generic/TypeName.hpp
    )
    SET(GENERIC_SOURCES
        Generic/TypeName.cpp
    )
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        Geometry/Geometry.hpp
        Geometry/GeometryConstructors.hpp
        Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        Geometry/Geometry.cpp
        Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        Geometry/GeometryImplementation/ConstantGeometry.hpp
        Geometry/GeometryImplementation/GenericGeometry.hpp
        Geometry/GeometryImplementation/GeometryImplementation.hpp
        Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        Geometry/GeometryImplementation/ConstantGeometry.cpp
        Geometry/GeometryImplementation/GenericGeometry.cpp
        Geometry/GeometryImplementation/GeometryImplementation.cpp
        Geometry/GeometryImplementation/SimplexGeometry.cpp
    )
    
    # Matrix directory files
    SET(MATRIX_HEADERS
        Matrix/DenseBasePlugin.hpp
        Matrix/Matrix.hpp
        Matrix/MatrixBasePlugin.hpp
        Matrix/MatrixPlugin.hpp
        Matrix/MatrixTests.hpp
        Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES
        Matrix/Matrix.cpp
    )

    # Mesh directory files
    SET(MESH_HEADERS
        Mesh/Mesh.hpp
    )
    SET(MESH_SOURCES
        Mesh/Mesh.cpp
    )

    # Object directory files
    SET(OBJECT_HEADERS
        Object/Object.hpp
        Object/ObjectTests.hpp
    )
    SET(OBJECT_SOURCES
        Object/Object.cpp
    )
    
    # Scalar directory files
    SET(SCALAR_HEADERS
        Scalar/Comparison.hpp
        Scalar/Interval.hpp
        Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        Scalar/Interval.cpp
    )
    
    # Set directory files
    SET(SET_HEADERS
        Set/Set.hpp
        Set/SetNode.hpp
        Set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS
        Simplex/Simplex.hpp
        Simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        Simplex/Simplex.cpp
    )
    
    # Update global source list
    ADD_TO_GLOBAL_SOURCE_LIST(
        ${CORE_FILES}
        ${COMMON_HEADERS}
        ${COMMON_SOURCES}
        Common/serialization.proto
        ${DATABASE_HEADERS}
        ${DATABASE_SOURCES}
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
        ${GENERIC_HEADERS}
        ${GENERIC_SOURCES}
        ${GEOMETRY_HEADERS}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_HEADERS}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_HEADERS}
        ${MATRIX_SOURCES}
        ${MESH_HEADERS}
        ${MESH_SOURCES}
        ${OBJECT_HEADERS}
        ${OBJECT_SOURCES}
        ${SCALAR_HEADERS}
        ${SCALAR_SOURCES}
        ${SET_HEADERS}
        ${SET_SOURCES}
        ${SIMPLEX_HEADERS}
        ${SIMPLEX_SOURCES}
    )
    
########## Compile OpenSolidCore library ##########

    COMPILE_PROTO_FILES(PROTO_SOURCES Common/serialization.proto)

    ADD_LIBRARY(OpenSolidCore SHARED
        ${PROTO_SOURCES}
        ${COMMON_SOURCES}
        ${GENERIC_SOURCES}
        ${DATUM_SOURCES}
        ${DOMAIN_SOURCES}
        ${DOMAINIMPLEMENTATION_SOURCES}
        ${FILE_SOURCES}
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_SOURCES}
        ${MESH_SOURCES}
        ${OBJECT_SOURCES}
        ${SCALAR_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
    )
    SET_TARGET_PROPERTIES(OpenSolidCore PROPERTIES DEBUG_POSTFIX "d")
    TARGET_LINK_LIBRARIES(OpenSolidCore libprotobuf libsqlite3)
    
########## Compile tests ##########

    ADD_CXXTEST(IntervalTests Scalar/IntervalTests OpenSolidCore)
    ADD_CXXTEST(MatrixTests Matrix/MatrixTests OpenSolidCore)
    ADD_CXXTEST(DatumTests Datum/DatumTests OpenSolidCore)
    ADD_CXXTEST(SetTests Set/SetTests OpenSolidCore)
    ADD_CXXTEST(FunctionTests Function/FunctionTests OpenSolidCore)
    ADD_CXXTEST(GeometryTests Geometry/GeometryTests OpenSolidCore)
    ADD_CXXTEST(SimplexTests Simplex/SimplexTests OpenSolidCore)
    ADD_CXXTEST(ObjectTests Object/ObjectTests OpenSolidCore)
    ADD_CXXTEST(FileTests File/FileTests OpenSolidCore)
    
########## Temporary fix - define 'override' as empty macro for GCC < 4.7 ##########
    
    IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
        SET_TARGET_PROPERTIES(
            OpenSolidCore
            IntervalTests
            MatrixTests
            DatumTests
            SetTests
            FunctionTests
            GeometryTests
            SimplexTests
            ObjectTests
            FileTests
            PROPERTIES
            COMPILE_FLAGS
            "-Doverride="
        )
    ENDIF()
    
########## Install headers ##########
    
    INSTALL(DIRECTORY .
        DESTINATION include/opensolid
        FILES_MATCHING
        PATTERN *.hpp
        PATTERN *Tests.hpp EXCLUDE
        PATTERN Template*.hpp EXCLUDE
    )
    
########## Install libraries ##########
        
    # Install C++ shared libraries
    INSTALL(TARGETS OpenSolidCore
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
