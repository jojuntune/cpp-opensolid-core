######################################################################
#                                                                    #
#                             CONFIGURE                              #
#                                                                    #
######################################################################

########## General setup ##########

    PROJECT(OpenSolid)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
    ENABLE_TESTING()

    # Enable M_PI, M_PI_2, M_E, M_SQRT2 macros
    ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

    # GCC-specific compiler flags
    IF (CMAKE_COMPILER_IS_GNUCXX)
        # Enable C++0x and add extra warning flags
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wno-unused-variable")
        # Enable -fPIC on 64-bit systems where it is required
        IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF (GCC_VERSION VERSION_LESS 4.6)
            ADD_DEFINITIONS(-Dnullptr=0)
        ENDIF (GCC_VERSION VERSION_LESS 4.6)
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)

    # FreeBSD-specific compiler flags
    IF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
        # Use -pthread compilation option to properly link to threading library
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    
    # Windows-specific compiler flags
    IF (WIN32)
        # Make sure min/max macros are not defined by windows.h (conflicts with interval min/max and
        # Eigen code), and avoid warning about boost string algorithms
        ADD_DEFINITIONS(-DNOMINMAX -D_SCL_SECURE_NO_WARNINGS)
    ENDIF (WIN32)

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
    
########## Define lists of source files ##########

    # OpenSolid directory files
    SET(OPENSOLID_FILES
        bindTemplate.cpp
        config.hpp
        Template.cpp
        Template.hpp
        TemplateTests.hpp
    )
    
    # Common directory files
    SET(COMMON_HEADERS
        Common/Bounds.hpp
        Common/BoundsTests.hpp
        Common/Convertible.hpp
        Common/Error.hpp
        Common/ReferenceCounted.hpp
        Common/Transformable.hpp
    )
    SET(COMMON_SOURCES Common/Error.cpp)
    
    # Datum directory files
    SET(DATUM_HEADERS
        Datum/Axis.hpp
        Datum/CoordinateSystem.hpp
        Datum/Datum.hpp
        Datum/DatumTests.hpp
        Datum/Frame.hpp
        Datum/Plane.hpp
    )
    SET(DATUM_SOURCES
        Datum/Axis.cpp
        Datum/CoordinateSystem.cpp
        Datum/Datum.cpp
        Datum/Frame.cpp
        Datum/Plane.cpp
    )
    
    # Domain directory files
    SET(DOMAIN_HEADERS Domain/Domain.hpp Domain/DomainConstructors.hpp)
    SET(DOMAIN_SOURCES Domain/Domain.cpp Domain/DomainConstructors.cpp)

    # Domain/DomainImplementation directory files
    SET(DI_HEADERS
        Domain/DomainImplementation/DomainImplementation.hpp
        Domain/DomainImplementation/GenericDomain.hpp
        Domain/DomainImplementation/IntervalDomain.hpp
        Domain/DomainImplementation/RectangleDomain.hpp
        Domain/DomainImplementation/CuboidDomain.hpp
        Domain/DomainImplementation/SimplexDomain.hpp
    )
    SET(DI_SOURCES
        Domain/DomainImplementation/DomainImplementation.cpp
        Domain/DomainImplementation/GenericDomain.cpp
        Domain/DomainImplementation/IntervalDomain.cpp
        Domain/DomainImplementation/RectangleDomain.cpp
        Domain/DomainImplementation/CuboidDomain.cpp
        Domain/DomainImplementation/SimplexDomain.cpp
    )
    
    # Evaluation directory files
    SET(EVALUATION_HEADERS Evaluation/Evaluation.hpp Evaluation/MatrixArgument.hpp)
    SET(EVALUATION_SOURCES)
    
    # Function directory files
    SET(FUNCTION_HEADERS
        Function/Function.hpp
        Function/FunctionConstructors.hpp
        Function/FunctionTests.hpp
        Function/FunctionResult.hpp
    )
    SET(FUNCTION_SOURCES Function/Function.cpp Function/FunctionConstructors.cpp)
    
    # Function/FunctionImplementation directory files
    SET(FI_HEADERS
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
    SET(FI_SOURCES
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
    
    # Geometry directory files
    SET(GEOMETRY_HEADERS
        Geometry/Geometry.hpp
        Geometry/GeometryConstructors.hpp
        Geometry/GeometryResult.hpp
        Geometry/GeometryTests.hpp
    )
    SET(GEOMETRY_SOURCES
        Geometry/Geometry.cpp
        Geometry/GeometryConstructors.cpp
    )

    # Geometry/GeometryImplementation directory files
    SET(GI_HEADERS
        Geometry/GeometryImplementation/ConstantGeometry.hpp
        Geometry/GeometryImplementation/GenericGeometry.hpp
        Geometry/GeometryImplementation/GeometryImplementation.hpp
        Geometry/GeometryImplementation/SimplexGeometry.hpp
    )
    SET(GI_SOURCES
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
        Matrix/MatrixTests.hpp
        Matrix/MatrixIterator.hpp
    )
    SET(MATRIX_SOURCES)

    # Model directory files
    SET(MODEL_HEADERS Model/Model.hpp)
    SET(MODEL_SOURCES Model/Model.cpp)
    
    # Python directory files
    SET(PYTHON_HEADERS Python/BoostPython.hpp Python/check.hpp)
    SET(PYTHON_SOURCES
        Python/bindComparison.cpp
        Python/bindDatum.cpp
        Python/bindError.cpp
        Python/bindFunction.cpp
        Python/bindDouble.cpp
        Python/bindInterval.cpp
        Python/bindMatrix.cpp
        Python/bindMatrixConstructors.cpp
        Python/bindSimplex.cpp
        Python/check.cpp
        Python/module.cpp
    )

    # Scalar directory files
    SET(SCALAR_HEADERS
        Scalar/Comparison.hpp
        Scalar/double.hpp
        Scalar/Interval.hpp
        Scalar/IntervalTests.hpp
    )
    SET(SCALAR_SOURCES Scalar/Interval.cpp)
    
    # Script directory files
    SET(SCRIPT_HEADERS Script/Script.hpp Script/ScriptTests.hpp)
    SET(SCRIPT_SOURCES Script/Script.cpp)
    
    # Set directory files
    SET(SET_HEADERS Set/Set.hpp Set/SetTests.hpp Set/SetNode.hpp)
    SET(SET_SOURCES)
    
    # Simplex directory files
    SET(SIMPLEX_HEADERS Simplex/Simplex.hpp Simplex/SimplexTests.hpp)
    SET(SIMPLEX_SOURCES Simplex/Simplex.cpp)

    # Support directory files
    SET(SUPPORT_HEADERS Support/declarations.hpp Support/Boost.hpp Support/STL.hpp)
    SET(SUPPORT_SOURCES)
    
########## Set up source groups for Visual Studio ##########

    ADD_LIBRARY(ALL_SOURCES EXCLUDE_FROM_ALL
        ${OPENSOLID_FILES}
        ${COMMON_HEADERS}
        ${COMMON_SOURCES}
        ${DATUM_HEADERS}
        ${DATUM_SOURCES}
        ${DOMAIN_HEADERS}
        ${DOMAIN_SOURCES}
        ${DI_HEADERS}
        ${DI_SOURCES}
        ${EVALUATION_HEADERS}
        ${EVALUATION_SOURCES}
        ${FUNCTION_HEADERS}
        ${FUNCTION_SOURCES}
        ${FI_HEADERS}
        ${FI_SOURCES}
        ${GEOMETRY_HEADERS}
        ${GEOMETRY_SOURCES}
        ${GI_HEADERS}
        ${GI_SOURCES}
        ${MATRIX_HEADERS}
        ${MATRIX_SOURCES}
        ${MODEL_HEADERS}
        ${MODEL_SOURCES}
        ${PYTHON_HEADERS}
        ${PYTHON_SOURCES}
        ${SCALAR_HEADERS}
        ${SCALAR_SOURCES}
        ${SCRIPT_HEADERS}
        ${SCRIPT_SOURCES}
        ${SET_HEADERS}
        ${SET_SOURCES}
        ${SIMPLEX_HEADERS}
        ${SIMPLEX_SOURCES}
        ${SUPPORT_HEADERS}
        ${SUPPORT_SOURCES}
    )
    
    SOURCE_GROUP(OpenSolid FILES ${OPENSOLID_FILES})
    SOURCE_GROUP(OpenSolid\\Common FILES ${COMMON_HEADERS} ${COMMON_SOURCES})
    SOURCE_GROUP(OpenSolid\\Datum FILES ${DATUM_HEADERS} ${DATUM_SOURCES})
    SOURCE_GROUP(OpenSolid\\Domain FILES ${DOMAIN_HEADERS} ${DOMAIN_SOURCES})
    SOURCE_GROUP(OpenSolid\\Domain\\DomainImplementation FILES ${DI_HEADERS} ${DI_SOURCES})
    SOURCE_GROUP(OpenSolid\\Evaluation FILES ${EVALUATION_HEADERS} ${EVALUATION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    SOURCE_GROUP(OpenSolid\\Function\\FunctionImplementation FILES ${FI_HEADERS} ${FI_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    SOURCE_GROUP(OpenSolid\\Geometry\\GeometryImplementation FILES ${GI_HEADERS} ${GI_SOURCES})
    SOURCE_GROUP(OpenSolid\\Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    SOURCE_GROUP(OpenSolid\\Model FILES ${MODEL_HEADERS} ${MODEL_SOURCES})
    SOURCE_GROUP(OpenSolid\\Python FILES ${PYTHON_HEADERS} ${PYTHON_SOURCES})
    SOURCE_GROUP(OpenSolid\\Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    SOURCE_GROUP(OpenSolid\\Script FILES ${SCRIPT_HEADERS} ${SCRIPT_SOURCES})
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
        ${DI_SOURCES}
        ${EVALUATION_SOURCES}
        ${FUNCTION_SOURCES}
        ${FI_SOURCES}
        ${GEOMETRY_SOURCES}
        ${GI_SOURCES}
        ${MATRIX_SOURCES}
        ${MODEL_SOURCES}
        ${PRIMITIVE_SOURCES}
        ${SCALAR_SOURCES}
        ${SET_SOURCES}
        ${SIMPLEX_SOURCES}
    )
    
########## Compile Python extension module ##########
    
    ADD_LIBRARY(opensolid SHARED ${PYTHON_SOURCES})
    SET_TARGET_PROPERTIES(opensolid PROPERTIES PREFIX "")
    IF(WIN32)
        SET_TARGET_PROPERTIES(opensolid PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32)
    TARGET_LINK_LIBRARIES(opensolid OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
########## Compile OpenSolidScript library ##########
    
    ADD_LIBRARY(OpenSolidScript SHARED ${SCRIPT_SOURCES})
    TARGET_LINK_LIBRARIES(OpenSolidScript
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
    ADD_CXXTEST(ScriptTests Script/ScriptTests.hpp OpenSolidScript OpenSolidCore)
    ADD_CXXTEST(BoundsTests Common/BoundsTests.hpp OpenSolidCore)
    
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
    INSTALL(TARGETS OpenSolidCore OpenSolidScript opensolid
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )

    # Install Python extension module
    INSTALL(TARGETS opensolid DESTINATION ${PYTHON_SITE_PACKAGES})
