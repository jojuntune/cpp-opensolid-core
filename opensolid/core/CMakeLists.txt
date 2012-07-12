########## Set up Boost ##########

    FIND_PACKAGE(Boost REQUIRED)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

########## Define lists of source files ##########

    # core directory files
    SET(CORE_FILES
        CMakeLists.txt
        config.hpp
        Template.cpp
        Template.hpp
        TemplateTests.hpp
    )
    
    # common directory files
    SET(COMMON_HEADERS
        common/Error.hpp
        common/Evaluation.hpp
    )
    SET(COMMON_SOURCES
        common/Error.cpp
    )
    
    # datum directory files
    SET(DATUM_HEADERS
        datum/Axis.hpp
        datum/Datum.hpp
        datum/DatumTests.hpp
        datum/Frame.hpp
        datum/Plane.hpp
    )
    SET(DATUM_SOURCES
        datum/Axis.cpp
        datum/Datum.cpp
        datum/Frame.cpp
        datum/Plane.cpp
    )
    
    # domain directory files
    SET(DOMAIN_HEADERS
        domain/Domain.hpp
        domain/DomainConstructors.hpp
    )
    SET(DOMAIN_SOURCES
        domain/Domain.cpp
        domain/DomainConstructors.cpp
    )

    # domain/domainImplementation directory files
    SET(DOMAINIMPLEMENTATION_HEADERS
        domain/domainimplementation/DomainImplementation.hpp
        domain/domainimplementation/GenericDomain.hpp
        domain/domainimplementation/IntervalDomain.hpp
        domain/domainimplementation/RectangleDomain.hpp
        domain/domainimplementation/CuboidDomain.hpp
        domain/domainimplementation/SimplexDomain.hpp
    )
    SET(DOMAINIMPLEMENTATION_SOURCES
        domain/domainimplementation/DomainImplementation.cpp
        domain/domainimplementation/GenericDomain.cpp
        domain/domainimplementation/IntervalDomain.cpp
        domain/domainimplementation/RectangleDomain.cpp
        domain/domainimplementation/CuboidDomain.cpp
        domain/domainimplementation/SimplexDomain.cpp
    )
    
    # function directory files
    SET(FUNCTION_HEADERS
        function/Function.hpp
        function/FunctionConstructors.hpp
        function/FunctionTests.hpp
    )
    SET(FUNCTION_SOURCES
        function/Function.cpp
        function/FunctionConstructors.cpp
    )
    
    # function/functionimplementation directory files
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        function/functionimplementation/ArccosineFunction.hpp
        function/functionimplementation/ArcsineFunction.hpp
        function/functionimplementation/BinaryOperation.hpp
        function/functionimplementation/ComponentsFunction.hpp
        function/functionimplementation/CompositionFunction.hpp
        function/functionimplementation/ConcatenationFunction.hpp
        function/functionimplementation/ConstantFunction.hpp
        function/functionimplementation/CosineFunction.hpp
        function/functionimplementation/CrossProductFunction.hpp
        function/functionimplementation/DifferenceFunction.hpp
        function/functionimplementation/DotProductFunction.hpp
        function/functionimplementation/EllipticalFunction.hpp
        function/functionimplementation/ExponentialFunction.hpp
        function/functionimplementation/FunctionImplementation.hpp
        function/functionimplementation/LinearFunction.hpp
        function/functionimplementation/LogarithmFunction.hpp
        function/functionimplementation/NegationFunction.hpp
        function/functionimplementation/NormalizedFunction.hpp
        function/functionimplementation/NormFunction.hpp
        function/functionimplementation/ParametersFunction.hpp
        function/functionimplementation/PowerFunction.hpp
        function/functionimplementation/ProductFunction.hpp
        function/functionimplementation/QuotientFunction.hpp
        function/functionimplementation/SineFunction.hpp
        function/functionimplementation/SquaredNormFunction.hpp
        function/functionimplementation/SquareRootFunction.hpp
        function/functionimplementation/SumFunction.hpp
        function/functionimplementation/TangentFunction.hpp
        function/functionimplementation/TransformedFunction.hpp
        function/functionimplementation/UnaryOperation.hpp
    )
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        function/functionimplementation/ArccosineFunction.cpp
        function/functionimplementation/ArcsineFunction.cpp
        function/functionimplementation/BinaryOperation.cpp
        function/functionimplementation/ComponentsFunction.cpp
        function/functionimplementation/CompositionFunction.cpp
        function/functionimplementation/ConcatenationFunction.cpp
        function/functionimplementation/ConstantFunction.cpp
        function/functionimplementation/CosineFunction.cpp
        function/functionimplementation/CrossProductFunction.cpp
        function/functionimplementation/DifferenceFunction.cpp
        function/functionimplementation/DotProductFunction.cpp
        function/functionimplementation/EllipticalFunction.cpp
        function/functionimplementation/ExponentialFunction.cpp
        function/functionimplementation/FunctionImplementation.cpp
        function/functionimplementation/LinearFunction.cpp
        function/functionimplementation/LogarithmFunction.cpp
        function/functionimplementation/NegationFunction.cpp
        function/functionimplementation/NormalizedFunction.cpp
        function/functionimplementation/NormFunction.cpp
        function/functionimplementation/ParametersFunction.cpp
        function/functionimplementation/PowerFunction.cpp
        function/functionimplementation/ProductFunction.cpp
        function/functionimplementation/QuotientFunction.cpp
        function/functionimplementation/SineFunction.cpp
        function/functionimplementation/SquaredNormFunction.cpp
        function/functionimplementation/SquareRootFunction.cpp
        function/functionimplementation/SumFunction.cpp
        function/functionimplementation/TangentFunction.cpp
        function/functionimplementation/TransformedFunction.cpp
        function/functionimplementation/UnaryOperation.cpp
    )

    # generic directory files
    SET(GENERIC_HEADERS
        generic/Bounds.hpp
        generic/Conversion.hpp
        generic/ReferenceCounted.hpp
        generic/Transformable.hpp
        generic/TypeName.hpp
    )
    SET(GENERIC_SOURCES
        generic/TypeName.cpp
    )
    
    # geometry directory files
    SET(GEOMETRY_HEADERS
        geometry/Geometry.hpp
        geometry/GeometryConstructors.hpp
        geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        geometry/Geometry.cpp
        geometry/GeometryConstructors.cpp
    )

    # geometry/geometryimplementation directory files
    SET(GEOMETRYIMPLEMENTATION_HEADERS
        geometry/geometryimplementation/ConstantGeometry.hpp
        geometry/geometryimplementation/GenericGeometry.hpp
        geometry/geometryimplementation/GeometryImplementation.hpp
        geometry/geometryimplementation/SimplexGeometry.hpp
    )
    SET(GEOMETRYIMPLEMENTATION_SOURCES
        geometry/geometryimplementation/ConstantGeometry.cpp
        geometry/geometryimplementation/GenericGeometry.cpp
        geometry/geometryimplementation/GeometryImplementation.cpp
        geometry/geometryimplementation/SimplexGeometry.cpp
    )
    
    # matrix directory files
    SET(MATRIX_HEADERS
        matrix/DenseBasePlugin.hpp
        matrix/Matrix.hpp
        matrix/MatrixBasePlugin.hpp
        matrix/MatrixPlugin.hpp
        matrix/MatrixTests.hpp
        matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES
        matrix/Matrix.cpp
    )

    # mesh directory files
    SET(MESH_HEADERS
        mesh/Mesh.hpp
    )
    SET(MESH_SOURCES
        mesh/Mesh.cpp
    )
    
    # scalar directory files
    SET(SCALAR_HEADERS
        scalar/Comparison.hpp
        scalar/Interval.hpp
        scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES
        scalar/Interval.cpp
    )
    
    # set directory files
    SET(SET_HEADERS
        set/Set.hpp
        set/SetNode.hpp
        set/SetTests.hpp
    )
    SET(SET_SOURCES
    )
    
    # simplex directory files
    SET(SIMPLEX_HEADERS
        simplex/Simplex.hpp
        simplex/SimplexTests.hpp
    )
    SET(SIMPLEX_SOURCES
        simplex/Simplex.cpp
    )
    
    # Update global source list
    ADD_TO_GLOBAL_SOURCE_LIST(
        ${CORE_FILES}
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
        ${SCALAR_HEADERS}
        ${SCALAR_SOURCES}
        ${SET_HEADERS}
        ${SET_SOURCES}
        ${SIMPLEX_HEADERS}
        ${SIMPLEX_SOURCES}
    )
    
########## Compile OpenSolidCore library ##########

    ADD_LIBRARY(OpenSolidCore SHARED
        ${COMMON_SOURCES}
        ${GENERIC_SOURCES}
        ${DATUM_SOURCES}
        ${DOMAIN_SOURCES}
        ${DOMAINIMPLEMENTATION_SOURCES}
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${GEOMETRYIMPLEMENTATION_SOURCES}
        ${MATRIX_SOURCES}
        ${MESH_SOURCES}
        ${SCALAR_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
    )
    SET_TARGET_PROPERTIES(OpenSolidCore PROPERTIES DEBUG_POSTFIX "d")
    
########## Compile tests ##########

    ADD_CXXTEST(IntervalTests scalar/IntervalTests OpenSolidCore)
    ADD_CXXTEST(MatrixTests matrix/MatrixTests OpenSolidCore)
    ADD_CXXTEST(DatumTests datum/DatumTests OpenSolidCore)
    ADD_CXXTEST(SetTests set/SetTests OpenSolidCore)
    ADD_CXXTEST(FunctionTests function/FunctionTests OpenSolidCore)
    ADD_CXXTEST(GeometryTests geometry/GeometryTests OpenSolidCore)
    ADD_CXXTEST(SimplexTests simplex/SimplexTests OpenSolidCore)
    
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
