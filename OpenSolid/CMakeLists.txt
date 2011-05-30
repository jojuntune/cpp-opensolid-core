# Collect source files

SET(FUNCTION_SOURCES
    Function/Function.cpp
    Function/FunctionImplementation.cpp
    Function/implementations/ArccosineFunction.cpp
    Function/implementations/ArcsineFunction.cpp
    Function/implementations/BinaryFunction.cpp
    Function/implementations/ComponentsFunction.cpp
    Function/implementations/CompositionFunction.cpp
    Function/implementations/ConcatenationFunction.cpp
    Function/implementations/ConstantFunction.cpp
    Function/implementations/CosineFunction.cpp
    Function/implementations/CrossProductFunction.cpp
    Function/implementations/DifferenceFunction.cpp
    Function/implementations/DotProductFunction.cpp
    Function/implementations/EllipticalFunction.cpp
    Function/implementations/LinearFunction.cpp
    Function/implementations/NegationFunction.cpp
    Function/implementations/NormFunction.cpp
    Function/implementations/NormalizedFunction.cpp
    Function/implementations/ParametersFunction.cpp
    Function/implementations/ProductFunction.cpp
    Function/implementations/QuotientFunction.cpp
    Function/implementations/SineFunction.cpp
    Function/implementations/SquaredNormFunction.cpp
    Function/implementations/SquareRootFunction.cpp
    Function/implementations/SumFunction.cpp
    Function/implementations/TangentFunction.cpp
    Function/implementations/TransformedFunction.cpp
    Function/implementations/UnaryFunction.cpp
)

SET(GEOMETRY_SOURCES
    Geometry/Geometry.cpp
)

SET(DOMAIN_SOURCES
    Domain/Domain.cpp
)

ADD_LIBRARY(OpenSolid SHARED
    Common/Error.cpp
    Interval/Interval.cpp
    Interval/Tolerance.cpp
    Datum/Datum.cpp
    ${FUNCTION_SOURCES}
    ${GEOMETRY_SOURCES}
    ${DOMAIN_SOURCES}
)
    
INSTALL(
    TARGETS OpenSolid
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

ADD_CXXTEST(Interval.tests Interval/Interval.tests.hpp OpenSolid)
ADD_CXXTEST(Matrix.tests Matrix/Matrix.tests.hpp OpenSolid)
ADD_CXXTEST(Datum.tests Datum/Datum.tests.hpp OpenSolid)
ADD_CXXTEST(Set.tests Set/Set.tests.hpp OpenSolid)
ADD_CXXTEST(Function.tests Function/Function.tests.hpp OpenSolid)
ADD_CXXTEST(Geometry.tests Geometry/Geometry.tests.hpp OpenSolid)
ADD_CXXTEST(Simplex.tests Simplex/Simplex.tests.hpp OpenSolid)
