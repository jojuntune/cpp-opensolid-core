########## Create macro for .proto file compilation ##########

    # MACRO(COMPILE_PROTO_FILES GENERATED_SOURCES)
    #     SET(${GENERATED_SOURCES})
    #     FOREACH(FULL_NAME ${ARGN})
    #         GET_FILENAME_COMPONENT(FILE_PATH ${FULL_NAME} PATH)
    #         GET_FILENAME_COMPONENT(BASE_NAME ${FULL_NAME} NAME_WE)
    #         ADD_CUSTOM_COMMAND(
    #             OUTPUT
    #             "${FILE_PATH}/${BASE_NAME}.pb.h"
    #             "${FILE_PATH}/${BASE_NAME}.pb.cc"
    #             DEPENDS
    #             protoc
    #             "${FULL_NAME}"
    #             COMMAND
    #             protoc
    #             ARGS
    #             --proto_path="${FILE_PATH}"
    #             --cpp_out="${FILE_PATH}"
    #             "${FULL_NAME}"
    #         )
    #         LIST(APPEND ${GENERATED_SOURCES} "${FILE_PATH}/${BASE_NAME}.pb.cc")
    #     ENDFOREACH(FULL_NAME)
    # ENDMACRO(COMPILE_PROTO_FILES)
    
########## Compile OpenSolidIO library ##########
    
    include_directories(${SQLITE_ROOT})

    file(GLOB IO_SOURCES *.cpp)
    add_library(OpenSolidIO SHARED ${IO_SOURCES})
    set_target_properties(OpenSolidIO PROPERTIES DEBUG_POSTFIX d)
    target_link_libraries(OpenSolidIO OpenSolidCore)
    
########## Install OpenSolidIO library ##########
        
    install(
        TARGETS OpenSolidIO
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
