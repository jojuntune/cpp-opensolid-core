########## Define lists of source files ##########

    SET(LIBPROTOBUF_SOURCES
        ${OpenSolid}/External/google/protobuf/descriptor.cc
        ${OpenSolid}/External/google/protobuf/descriptor.pb.cc
        ${OpenSolid}/External/google/protobuf/descriptor_database.cc
        ${OpenSolid}/External/google/protobuf/dynamic_message.cc
        ${OpenSolid}/External/google/protobuf/extension_set.cc
        ${OpenSolid}/External/google/protobuf/extension_set_heavy.cc
        ${OpenSolid}/External/google/protobuf/generated_message_reflection.cc
        ${OpenSolid}/External/google/protobuf/generated_message_util.cc
        ${OpenSolid}/External/google/protobuf/message.cc
        ${OpenSolid}/External/google/protobuf/message_lite.cc
        ${OpenSolid}/External/google/protobuf/reflection_ops.cc
        ${OpenSolid}/External/google/protobuf/repeated_field.cc
        ${OpenSolid}/External/google/protobuf/service.cc
        ${OpenSolid}/External/google/protobuf/text_format.cc
        ${OpenSolid}/External/google/protobuf/unknown_field_set.cc
        ${OpenSolid}/External/google/protobuf/wire_format.cc
        ${OpenSolid}/External/google/protobuf/wire_format_lite.cc
        ${OpenSolid}/External/google/protobuf/io/coded_stream.cc
        ${OpenSolid}/External/google/protobuf/io/gzip_stream.cc
        ${OpenSolid}/External/google/protobuf/io/printer.cc
        ${OpenSolid}/External/google/protobuf/io/tokenizer.cc
        ${OpenSolid}/External/google/protobuf/io/zero_copy_stream.cc
        ${OpenSolid}/External/google/protobuf/io/zero_copy_stream_impl.cc
        ${OpenSolid}/External/google/protobuf/io/zero_copy_stream_impl_lite.cc
        ${OpenSolid}/External/google/protobuf/stubs/common.cc
        ${OpenSolid}/External/google/protobuf/stubs/once.cc
        ${OpenSolid}/External/google/protobuf/stubs/structurally_valid.cc
        ${OpenSolid}/External/google/protobuf/stubs/strutil.cc
        ${OpenSolid}/External/google/protobuf/stubs/substitute.cc
        ${OpenSolid}/External/google/protobuf/compiler/importer.cc
        ${OpenSolid}/External/google/protobuf/compiler/parser.cc
    )
    
    SET(LIBPROTOC_SOURCES
        ${OpenSolid}/External/google/protobuf/compiler/code_generator.cc
        ${OpenSolid}/External/google/protobuf/compiler/command_line_interface.cc
        ${OpenSolid}/External/google/protobuf/compiler/plugin.cc
        ${OpenSolid}/External/google/protobuf/compiler/plugin.pb.cc
        ${OpenSolid}/External/google/protobuf/compiler/subprocess.cc
        ${OpenSolid}/External/google/protobuf/compiler/zip_writer.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_enum.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_enum_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_extension.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_file.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_generator.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_helpers.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_message.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_message_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_primitive_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_service.cc
        ${OpenSolid}/External/google/protobuf/compiler/cpp/cpp_string_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_enum.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_enum_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_extension.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_file.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_generator.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_helpers.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_message.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_message_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_primitive_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_service.cc
        ${OpenSolid}/External/google/protobuf/compiler/java/java_string_field.cc
        ${OpenSolid}/External/google/protobuf/compiler/python/python_generator.cc
    )
    
    SET(PROTOC_SOURCES
        ${OpenSolid}/External/google/protobuf/compiler/main.cc        
    )
    
    SET(GLOBAL_SOURCE_LIST ${GLOBAL_SOURCE_LIST} ${OpenSolid}/External/CMakeLists.txt PARENT_SCOPE)

########## Build Protocol Buffers libraries and compiler ##########

    ADD_LIBRARY(libprotobuf STATIC ${LIBPROTOBUF_SOURCES})
    ADD_LIBRARY(libprotoc STATIC ${LIBPROTOC_SOURCES})
    
    ADD_EXECUTABLE(protoc ${PROTOC_SOURCES})
    TARGET_LINK_LIBRARIES(protoc libprotobuf libprotoc)
    
    # Disable warnings for Protocol Buffers compilation
    IF (CMAKE_COMPILER_IS_GNUCXX)
        SET_TARGET_PROPERTIES(libprotobuf libprotoc protoc PROPERTIES COMPILE_FLAGS "-w")
    ELSEIF(WIN32)
        SET_TARGET_PROPERTIES(libprotobuf libprotoc protoc PROPERTIES COMPILE_FLAGS "/W0")
    ENDIF (CMAKE_COMPILER_IS_GNUCXX)
    
########## Install Eigen headers ##########
    
    INSTALL(DIRECTORY ${OpenSolid}/External/Eigen
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        PATTERN "CMakeLists.txt" EXCLUDE
    )
