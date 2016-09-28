########## Compile OpenSolidCore library ##########

    file(
        GLOB
        CORE_SOURCES
        *.cpp
        Intersection/*.cpp
        LazyCollection/*.cpp
        Matrix/*.cpp
        ParametricCurve/*.cpp
        ParametricExpression/*.cpp
        Position/*.cpp
        Simplex/*.cpp
        Variant/*.cpp
    )

    if(${BUILD_STATIC_LIBS})
        add_library(OpenSolidCore STATIC ${CORE_SOURCES})
        set_target_properties(OpenSolidCore PROPERTIES OUTPUT_NAME OpenSolidCoreStatic)
    else()
        add_library(OpenSolidCore SHARED ${CORE_SOURCES})
    endif()
    set_target_properties(OpenSolidCore PROPERTIES DEBUG_POSTFIX Debug)
    
########## Install OpenSolidCore headers and library ##########

    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION include/OpenSolid
        FILES_MATCHING PATTERN *.hpp
    )
        
    install(
        TARGETS OpenSolidCore
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
