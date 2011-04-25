# Collect source files
SET(COMMON_SOURCES common/Error.cpp common/check.cpp)
SET(VALUE_SOURCES value/Interval.cpp value/Tolerance.cpp value/check.cpp)
SET(DATUM_SOURCES datum/Datum.cpp)
SET(FUNCTION_SOURCES
    function/check.cpp
    function/Function.cpp
    function/FunctionImplementation.cpp
    function/implementations/BinaryFunction.cpp
    function/implementations/ComponentsFunction.cpp
    function/implementations/CompositionFunction.cpp
    function/implementations/ConcatenationFunction.cpp
    function/implementations/ConstantFunction.cpp
    function/implementations/CosineFunction.cpp
    function/implementations/CrossProductFunction.cpp
    function/implementations/DifferenceFunction.cpp
    function/implementations/DotProductFunction.cpp
    function/implementations/EllipticalFunction.cpp
    function/implementations/LinearFunction.cpp
    function/implementations/NegationFunction.cpp
    function/implementations/NormFunction.cpp
    function/implementations/NormalizedFunction.cpp
    function/implementations/ParametersFunction.cpp
    function/implementations/ProductFunction.cpp
    function/implementations/QuotientFunction.cpp
    function/implementations/SineFunction.cpp
    function/implementations/SquaredNormFunction.cpp
    function/implementations/SquareRootFunction.cpp
    function/implementations/SumFunction.cpp
    function/implementations/TangentFunction.cpp
    function/implementations/TransformedFunction.cpp
    function/implementations/UnaryFunction.cpp
)
SET(GEOMETRY_SOURCES geometry/Geometry.cpp geometry/Domain.cpp)

ADD_LIBRARY(opensolid SHARED
    ${COMMON_SOURCES}
    ${VALUE_SOURCES}
    ${DATUM_SOURCES}
    ${FUNCTION_SOURCES}
    ${GEOMETRY_SOURCES}
)
    
INSTALL(
    TARGETS opensolid
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

ADD_CXXTEST(Interval.tests value/Interval.tests.hpp opensolid)
ADD_CXXTEST(Matrix.tests value/Matrix.tests.hpp opensolid)
ADD_CXXTEST(Datum.tests datum/Datum.tests.hpp opensolid)
ADD_CXXTEST(List.tests collection/List.tests.hpp opensolid)
ADD_CXXTEST(Set.tests collection/Set.tests.hpp opensolid)
ADD_CXXTEST(Function.tests function/Function.tests.hpp opensolid)
ADD_CXXTEST(Geometry.tests geometry/Geometry.tests.hpp opensolid)
