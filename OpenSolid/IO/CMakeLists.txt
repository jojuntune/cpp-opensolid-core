########## Generate header and source from .proto file using protoc ##########

    set(MESSAGE_PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Messages.proto")

    set(GENERATED_MESSAGE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Messages.pb.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Messages.pb.h"
    )

    add_custom_command(
        OUTPUT
        ${GENERATED_MESSAGE_SOURCES}
        DEPENDS
        protoc
        ${MESSAGE_PROTO_FILE}
        COMMAND
        protoc
        ARGS
        --proto_path="${CMAKE_CURRENT_SOURCE_DIR}"
        --cpp_out="${CMAKE_CURRENT_SOURCE_DIR}"
        ${MESSAGE_PROTO_FILE}
    )
    
########## Compile OpenSolidIO library ##########

    #file(GLOB IO_SOURCES *.cpp)
    if(${BUILD_STATIC_LIBS})
        add_library(OpenSolidIO STATIC ${IO_SOURCES} ${GENERATED_MESSAGE_SOURCES})
        set_target_properties(OpenSolidIO PROPERTIES OUTPUT_NAME OpenSolidIOStatic)
    else()
        add_library(OpenSolidIO SHARED ${IO_SOURCES} ${GENERATED_MESSAGE_SOURCES})
    endif()
    set_target_properties(OpenSolidIO PROPERTIES DEBUG_POSTFIX Debug)
    target_link_libraries(OpenSolidIO OpenSolidCore protobuf)
    
########## Install OpenSolidIO headers and library ##########

    # install(
    #     DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    #     DESTINATION include/OpenSolid
    #     FILES_MATCHING PATTERN *.hpp
    # )
        
    # install(
    #     TARGETS OpenSolidIO
    #     RUNTIME DESTINATION bin
    #     LIBRARY DESTINATION lib
    #     ARCHIVE DESTINATION lib
    # )
