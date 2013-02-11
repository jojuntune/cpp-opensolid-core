########## Compile OpenSolidCore library ##########

    file(
        GLOB
        CORE_SOURCES
        *.cpp
        Datum/*.cpp
        Domain/*.cpp
        Function/*.cpp
        Geometry/*.cpp
        Interval/*.cpp
        Matrix/*.cpp
        Set/*.cpp
        Simplex/*.cpp
        Transformation/*.cpp
    )

    add_library(OpenSolidCore SHARED ${CORE_SOURCES})
    set_target_properties(OpenSolidCore PROPERTIES DEBUG_POSTFIX d)
    add_dependencies(OpenSolidCore eigen_sources)
    
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
    
########## Add files to global source list ##########

    add_to_global_source_list(
        *
        Datum/*
        Domain/*
        Function/*
        Geometry/*
        Interval/*
        Matrix/*
        Set/*
        Simplex/*
        Transformable/*
    )
