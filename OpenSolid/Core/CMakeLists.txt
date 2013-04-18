########## Compile OpenSolidCore library ##########

    file(
        GLOB
        CORE_SOURCES
        *.cpp
        Datum/*.cpp
        #Domain/*.cpp
        #DomainImplementation/*.cpp
        Function/*.cpp
        FunctionImplementation/*.cpp
        #Geometry/*.cpp
        Interval/*.cpp
        Matrix/*.cpp
        Set/*.cpp
        Simplex/*.cpp
        Transformation/*.cpp
    )

    add_library(OpenSolidCore SHARED ${CORE_SOURCES})
    add_library(OpenSolidCoreStatic STATIC ${CORE_SOURCES})
    set_target_properties(OpenSolidCore PROPERTIES DEBUG_POSTFIX Debug)
    set_target_properties(OpenSolidCoreStatic PROPERTIES DEBUG_POSTFIX Debug)
    add_dependencies(OpenSolidCore eigen_sources)
    add_dependencies(OpenSolidCoreStatic eigen_sources)
    
########## Install OpenSolidCore headers and library ##########

    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION include/OpenSolid
        FILES_MATCHING PATTERN *.hpp
    )
        
    install(
        TARGETS OpenSolidCore OpenSolidCoreStatic
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    
########## Add files to global source list ##########

    add_to_global_source_list(
        *
        Box/*
        Datum/*
        Domain/*
        DomainImplementation/*
        Function/*
        FunctionImplementation/*
        Geometry/*
        Interval/*
        Matrix/*
        Point/*
        Set/*
        Simplex/*
        Transformable/*
    )
