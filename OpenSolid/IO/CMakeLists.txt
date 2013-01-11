########## Generate header and source from .proto file using protoc ##########

    add_custom_command(
        OUTPUT
        "${CMAKE_CURRENT_SOURCE_DIR}/ObjectMessage.pb.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ObjectMessage.pb.cc"
        DEPENDS
        protoc
        "${CMAKE_CURRENT_SOURCE_DIR}/ObjectMessage.proto"
        COMMAND
        protoc
        ARGS
        --proto_path="${CMAKE_CURRENT_SOURCE_DIR}"
        --cpp_out="${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/ObjectMessage.proto"
    )
    
########## Compile OpenSolidIO library ##########

    file(GLOB IO_SOURCES *.cpp)
    add_library(OpenSolidIO SHARED ${IO_SOURCES} ObjectMessage.pb.cc)
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
