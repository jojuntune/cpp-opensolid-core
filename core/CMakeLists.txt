########## Define lists of source files ##########

    file(GLOB HEADERS *.hpp)
    file(GLOB SOURCES *.cpp)
    file(GLOB DETAIL_HEADERS detail/*.hpp)
    file(GLOB DETAIL_SOURCES detail/*.cpp)
    file(GLOB TEST_HEADERS tests/*.hpp)
    
    # Update global source list
    add_to_global_source_list(
        ${HEADERS}
        ${SOURCES}
        ${DETAIL_HEADERS}
        ${DETAIL_SOURCES}
        ${TEST_HEADERS}
        CMakeLists.txt
    )
    
########## Compile OpenSolidCore library ##########

    add_library(opensolidcore SHARED ${SOURCES} ${DETAIL_SOURCES})
    set_target_properties(opensolidcore PROPERTIES DEBUG_POSTFIX "d")
    
########## Compile tests ##########

    add_subdirectory(tests)
    
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
