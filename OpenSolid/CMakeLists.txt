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
        IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
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
    
######################################################################
#                                                                    #
#                               BUILD                                #
#                                                                    #
######################################################################
    
########## Compile libraries ##########

    # OpenSolidCore library

    SET(COMMON_SOURCES Common/Error.cpp)

    SET(SCALAR_SOURCES Scalar/Interval.cpp)
    
    SET(DATUM_SOURCES Datum/Datum.cpp)
    
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
    
    SET(DOMAIN_SOURCES Domain/Domain.cpp)
    
    SET(GEOMETRY_SOURCES Geometry/Geometry.cpp)
    
    ADD_LIBRARY(OpenSolidCore SHARED
        ${COMMON_SOURCES}
        ${SCALAR_SOURCES}
        ${DATUM_SOURCES}
        ${FUNCTION_SOURCES}
        ${GEOMETRY_SOURCES}
        ${DOMAIN_SOURCES}
    )
    
    # Python extension module
    
    # SET(PYTHON_SOURCES
    #     Python/check.cpp
    #     Python/bindError.cpp
    #     Python/bindInterval.cpp
    #     Python/bindMatrix.cpp
    #     Python/bindSpecificMatrixSizes.cpp
    #     Python/bindFunction.cpp
    #     Python/module.cpp
    # )
    # 
    # ADD_LIBRARY(opensolid SHARED ${PYTHON_SOURCES})
    # 
    # SET_TARGET_PROPERTIES(opensolid PROPERTIES PREFIX "")
    # 
    # IF(WIN32)
    #     SET_TARGET_PROPERTIES(opensolid PROPERTIES SUFFIX ".pyd")
    # ENDIF(WIN32)
    # 
    # TARGET_LINK_LIBRARIES(opensolid OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
    # OpenSolidScript library
    
    # ADD_LIBRARY(OpenSolidScript SHARED Script/Script.cpp)
    # 
    # TARGET_LINK_LIBRARIES(
    #     OpenSolidScript
    #     OpenSolidCore
    #     opensolid
    #     ${Boost_LIBRARIES}
    #     ${PYTHON_LIBRARIES}
    # )

    
    
########## Generate tests ##########

    ADD_CXXTEST(Interval.tests Interval/Interval.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Matrix.tests Matrix/Matrix.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Datum.tests Datum/Datum.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Set.tests Set/Set.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Function.tests Function/Function.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Geometry.tests Geometry/Geometry.tests.hpp OpenSolidCore)
    ADD_CXXTEST(Simplex.tests Simplex/Simplex.tests.hpp OpenSolidCore)
    # ADD_CXXTEST(Script.tests Script/Script.tests.hpp OpenSolidScript OpenSolidCore)
    
########## Install libraries and headers ##########
    
    # INSTALL(
    #     DIRECTORY ../External/Eigen
    #     DESTINATION include
    #     PATTERN "CMakeLists.txt" EXCLUDE
    # )
    # 
    # INSTALL(
    #     DIRECTORY ../OpenSolid
    #     DESTINATION include
    #     FILES_MATCHING PATTERN "*.hpp"
    #     PATTERN "*.tests.hpp" EXCLUDE
    # )
    #     
    # INSTALL(
    #     TARGETS OpenSolidCore opensolid OpenSolidScript
    #     RUNTIME DESTINATION bin
    #     LIBRARY DESTINATION lib
    #     ARCHIVE DESTINATION lib
    # )
