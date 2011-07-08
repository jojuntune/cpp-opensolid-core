######################################################################
#                                                                    #
#                             CONFIGURE                              #
#                                                                    #
######################################################################

########## General setup ##########

    PROJECT(OpenSolid)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
    ENABLE_TESTING()

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
    INCLUDE_DIRECTORIES(BEFORE .. ../External)
    
########## Set up Python ##########

    FIND_PACKAGE(PythonInterp REQUIRED)
    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

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
    
    SET(COMMON_HEADERS
        Common/config.hpp
        Common/Error.hpp
        Common/HashFunction.hpp
        Common/ReferenceCounted.hpp
        Common/ReferenceCountedBase.hpp
    )
    
    SET(COMMON_SOURCES
        Common/Error.cpp
    )
    
    SET(DATUM_HEADERS
        Datum/Axis.hpp
        Datum/CoordinateSystem.hpp
        Datum/Datum.hpp
        Datum/Datum.tests.hpp
        Datum/DatumExpressions.hpp
        Datum/Frame.hpp
        Datum/Plane.hpp
    )
    
    SET(DATUM_SOURCES
        Datum/Datum.cpp
    )
    
    SET(DOMAIN_HEADERS
        Domain/Domain.hpp
    )
    
    SET(DOMAIN_SOURCES
        Domain/Domain.cpp
    )
    
    SET(FUNCTION_HEADERS
        Function/Function.hpp
        Function/Function.tests.hpp
        Function/FunctionArgument.hpp
        Function/FunctionResult.hpp
    )
    
    SET(FUNCTION_SOURCES
        Function/Function.cpp
    )
    
    SET(FUNCTIONIMPLEMENTATION_HEADERS
        Function/FunctionImplementation/ArccosineFunction.hpp
        Function/FunctionImplementation/ArcsineFunction.hpp
        Function/FunctionImplementation/BinaryFunction.hpp
        Function/FunctionImplementation/ComponentsFunction.hpp
        Function/FunctionImplementation/CompositionFunction.hpp
        Function/FunctionImplementation/ConcatenationFunction.hpp
        Function/FunctionImplementation/ConstantFunction.hpp
        Function/FunctionImplementation/CosineFunction.hpp
        Function/FunctionImplementation/CrossProductFunction.hpp
        Function/FunctionImplementation/DifferenceFunction.hpp
        Function/FunctionImplementation/DotProductFunction.hpp
        Function/FunctionImplementation/EllipticalFunction.hpp
        Function/FunctionImplementation/FunctionImplementation.hpp
        Function/FunctionImplementation/LinearFunction.hpp
        Function/FunctionImplementation/NegationFunction.hpp
        Function/FunctionImplementation/NormalizedFunction.hpp
        Function/FunctionImplementation/NormFunction.hpp
        Function/FunctionImplementation/ParametersFunction.hpp
        Function/FunctionImplementation/ProductFunction.hpp
        Function/FunctionImplementation/QuotientFunction.hpp
        Function/FunctionImplementation/SineFunction.hpp
        Function/FunctionImplementation/SquaredNormFunction.hpp
        Function/FunctionImplementation/SquareRootFunction.hpp
        Function/FunctionImplementation/SumFunction.hpp
        Function/FunctionImplementation/TangentFunction.hpp
        Function/FunctionImplementation/TransformedFunction.hpp
        Function/FunctionImplementation/UnaryFunction.hpp
    )
    
    SET(FUNCTIONIMPLEMENTATION_SOURCES
        Function/FunctionImplementation/ArccosineFunction.cpp
        Function/FunctionImplementation/ArcsineFunction.cpp
        Function/FunctionImplementation/BinaryFunction.cpp
        Function/FunctionImplementation/ComponentsFunction.cpp
        Function/FunctionImplementation/CompositionFunction.cpp
        Function/FunctionImplementation/ConcatenationFunction.cpp
        Function/FunctionImplementation/ConstantFunction.cpp
        Function/FunctionImplementation/CosineFunction.cpp
        Function/FunctionImplementation/CrossProductFunction.cpp
        Function/FunctionImplementation/DifferenceFunction.cpp
        Function/FunctionImplementation/DotProductFunction.cpp
        Function/FunctionImplementation/EllipticalFunction.cpp
        Function/FunctionImplementation/FunctionImplementation.cpp
        Function/FunctionImplementation/LinearFunction.cpp
        Function/FunctionImplementation/NegationFunction.cpp
        Function/FunctionImplementation/NormalizedFunction.cpp
        Function/FunctionImplementation/NormFunction.cpp
        Function/FunctionImplementation/ParametersFunction.cpp
        Function/FunctionImplementation/ProductFunction.cpp
        Function/FunctionImplementation/QuotientFunction.cpp
        Function/FunctionImplementation/SineFunction.cpp
        Function/FunctionImplementation/SquaredNormFunction.cpp
        Function/FunctionImplementation/SquareRootFunction.cpp
        Function/FunctionImplementation/SumFunction.cpp
        Function/FunctionImplementation/TangentFunction.cpp
        Function/FunctionImplementation/TransformedFunction.cpp
        Function/FunctionImplementation/UnaryFunction.cpp
    )
    
    SET(GEOMETRY_HEADERS
        Geometry/Geometry.hpp
        Geometry/Geometry.tests.hpp
    )
    
    SET(GEOMETRY_SOURCES
        Geometry/Geometry.cpp
    )
    
    SET(MATRIX_HEADERS
        Matrix/DenseBasePlugin.hpp
        Matrix/Matrix.hpp
        Matrix/Matrix.tests.hpp
        Matrix/MatrixIterator.hpp
    )
    
    SET(MATRIX_SOURCES
    )
    
    SET(PYTHON_HEADERS
        Python/BoostPython.hpp
        Python/check.hpp
    )
    
    SET(PYTHON_SOURCES
        Python/bindDouble.cpp
        Python/bindError.cpp
        Python/bindFunction.cpp
        Python/bindInterval.cpp
        Python/bindMatrix.cpp
        Python/bindSpecificMatrixSizes.cpp
        Python/check.cpp
        Python/module.cpp
    )

    SET(SCALAR_HEADERS
        Scalar/Double.hpp
        Scalar/Interval.hpp
        Scalar/Interval.tests.hpp
    )

    SET(SCALAR_SOURCES
        Scalar/Interval.cpp
    )
    
    SET(SCRIPT_HEADERS
        Script/Script.hpp
        Script/Script.tests.hpp
    )
    
    SET(SCRIPT_SOURCES
        Script/Script.cpp
    )
    
    SET(SET_HEADERS
        Set/Set.hpp
        Set/Set.tests.hpp
        Set/SetNode.hpp
    )
    
    SET(SET_SOURCES
    )
    
    SET(SIMPLEX_HEADERS
        Simplex/Simplex.hpp
        Simplex/Simplex.tests.hpp
    )
    
    SET(SIMPLEX_SOURCES
    )
    
########## Set up source groups for Visual Studio ##########

    ADD_CUSTOM_TARGET(ALL_SOURCES SOURCES
        ${COMMON_HEADERS}
        ${COMMON_SOURCES}
        ${DATUM_HEADERS}
        ${DATUM_SOURCES}
        ${DOMAIN_HEADERS}
        ${DOMAIN_SOURCES}
        ${FUNCTION_HEADERS}
        ${FUNCTION_SOURCES}
        ${GEOMETRY_HEADERS}
        ${GEOMETRY_SOURCES}
        ${MATRIX_HEADERS}
        ${MATRIX_SOURCES}
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
    )
    
    SOURCE_GROUP(Common FILES ${COMMON_HEADERS} ${COMMON_SOURCES})
    SOURCE_GROUP(Datum FILES ${DATUM_HEADERS} ${DATUM_SOURCES})
    SOURCE_GROUP(Domain FILES ${DOMAIN_HEADERS} ${DOMAIN_SOURCES})
    SOURCE_GROUP(Function FILES ${FUNCTION_HEADERS} ${FUNCTION_SOURCES})
    SOURCE_GROUP(Function\\FunctionImplementation FILES
        ${FUNCTIONIMPLEMENTATION_HEADERS}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
    )
    SOURCE_GROUP(Geometry FILES ${GEOMETRY_HEADERS} ${GEOMETRY_SOURCES})
    SOURCE_GROUP(Matrix FILES ${MATRIX_HEADERS} ${MATRIX_SOURCES})
    SOURCE_GROUP(Python FILES ${PYTHON_HEADERS} ${PYTHON_SOURCES})
    SOURCE_GROUP(Scalar FILES ${SCALAR_HEADERS} ${SCALAR_SOURCES})
    SOURCE_GROUP(Script FILES ${SCRIPT_HEADERS} ${SCRIPT_SOURCES})
    SOURCE_GROUP(Set FILES ${SET_HEADERS} ${SET_SOURCES})
    SOURCE_GROUP(Simplex FILES ${SIMPLEX_HEADERS} ${SIMPLEX_SOURCES})
    
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
        ${FUNCTION_SOURCES}
        ${FUNCTIONIMPLEMENTATION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${MATRIX_SOURCES}
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
    
    TARGET_LINK_LIBRARIES(
        OpenSolidScript
        OpenSolidCore
        opensolid
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile tests ##########

    ADD_CXXTEST(Interval.tests Scalar/Interval.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Matrix.tests Matrix/Matrix.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Datum.tests Datum/Datum.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Set.tests Set/Set.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Function.tests Function/Function.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Geometry.tests Geometry/Geometry.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Simplex.tests Simplex/Simplex.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Script.tests Script/Script.tests.hpp OpenSolidScript OpenSolidCore)
    
######################################################################
#                                                                    #
#                              INSTALL                               #
#                                                                    #
######################################################################
    
########## Install Eigen headers ##########

    INSTALL(
        DIRECTORY ../External/Eigen
        DESTINATION include
        PATTERN "CMakeLists.txt" EXCLUDE
    )
    
########## Install OpenSolid headers ##########
    
    INSTALL(
        DIRECTORY ../OpenSolid
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN "*.tests.hpp" EXCLUDE
    )
    
########## Install libraries ##########
        
    INSTALL(
        TARGETS OpenSolidCore opensolid OpenSolidScript
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
