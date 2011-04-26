# Collect source files
SET(COMMON_SOURCES Common/Error.cpp Common/check.cpp)
SET(VALUE_SOURCES Value/Interval.cpp Value/Tolerance.cpp Value/check.cpp)
SET(DATUM_SOURCES Datum/Datum.cpp)
SET(FUNCTION_SOURCES
    Function/check.cpp
    Function/Function.cpp
    Function/FunctionImplementation.cpp
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
SET(GEOMETRY_SOURCES Geometry/Geometry.cpp Geometry/Domain.cpp)

ADD_LIBRARY(OpenSolid SHARED
    ${COMMON_SOURCES}
    ${VALUE_SOURCES}
    ${DATUM_SOURCES}
    ${FUNCTION_SOURCES}
    ${GEOMETRY_SOURCES}
)
    
INSTALL(
    TARGETS OpenSolid
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

ADD_CXXTEST(Interval.tests Value/Interval.tests.hpp OpenSolid)
ADD_CXXTEST(Matrix.tests Value/Matrix.tests.hpp OpenSolid)
ADD_CXXTEST(Datum.tests Datum/Datum.tests.hpp OpenSolid)
ADD_CXXTEST(List.tests Collection/List.tests.hpp OpenSolid)
ADD_CXXTEST(Set.tests Collection/Set.tests.hpp OpenSolid)
ADD_CXXTEST(Function.tests Function/Function.tests.hpp OpenSolid)
ADD_CXXTEST(Geometry.tests Geometry/Geometry.tests.hpp OpenSolid)
