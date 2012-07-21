########## Define lists of source files ##########

    SET(LIBPROTOBUF_SOURCES
        google/protobuf/descriptor.cc
        google/protobuf/descriptor.pb.cc
        google/protobuf/descriptor_database.cc
        google/protobuf/dynamic_message.cc
        google/protobuf/extension_set.cc
        google/protobuf/extension_set_heavy.cc
        google/protobuf/generated_message_reflection.cc
        google/protobuf/generated_message_util.cc
        google/protobuf/message.cc
        google/protobuf/message_lite.cc
        google/protobuf/reflection_ops.cc
        google/protobuf/repeated_field.cc
        google/protobuf/service.cc
        google/protobuf/text_format.cc
        google/protobuf/unknown_field_set.cc
        google/protobuf/wire_format.cc
        google/protobuf/wire_format_lite.cc
        google/protobuf/io/coded_stream.cc
        google/protobuf/io/gzip_stream.cc
        google/protobuf/io/printer.cc
        google/protobuf/io/tokenizer.cc
        google/protobuf/io/zero_copy_stream.cc
        google/protobuf/io/zero_copy_stream_impl.cc
        google/protobuf/io/zero_copy_stream_impl_lite.cc
        google/protobuf/stubs/common.cc
        google/protobuf/stubs/once.cc
        google/protobuf/stubs/structurally_valid.cc
        google/protobuf/stubs/strutil.cc
        google/protobuf/stubs/substitute.cc
        google/protobuf/compiler/importer.cc
        google/protobuf/compiler/parser.cc
    )
    
    SET(LIBPROTOC_SOURCES
        google/protobuf/compiler/code_generator.cc
        google/protobuf/compiler/command_line_interface.cc
        google/protobuf/compiler/plugin.cc
        google/protobuf/compiler/plugin.pb.cc
        google/protobuf/compiler/subprocess.cc
        google/protobuf/compiler/zip_writer.cc
        google/protobuf/compiler/cpp/cpp_enum.cc
        google/protobuf/compiler/cpp/cpp_enum_field.cc
        google/protobuf/compiler/cpp/cpp_extension.cc
        google/protobuf/compiler/cpp/cpp_field.cc
        google/protobuf/compiler/cpp/cpp_file.cc
        google/protobuf/compiler/cpp/cpp_generator.cc
        google/protobuf/compiler/cpp/cpp_helpers.cc
        google/protobuf/compiler/cpp/cpp_message.cc
        google/protobuf/compiler/cpp/cpp_message_field.cc
        google/protobuf/compiler/cpp/cpp_primitive_field.cc
        google/protobuf/compiler/cpp/cpp_service.cc
        google/protobuf/compiler/cpp/cpp_string_field.cc
        google/protobuf/compiler/java/java_enum.cc
        google/protobuf/compiler/java/java_enum_field.cc
        google/protobuf/compiler/java/java_extension.cc
        google/protobuf/compiler/java/java_field.cc
        google/protobuf/compiler/java/java_file.cc
        google/protobuf/compiler/java/java_generator.cc
        google/protobuf/compiler/java/java_helpers.cc
        google/protobuf/compiler/java/java_message.cc
        google/protobuf/compiler/java/java_message_field.cc
        google/protobuf/compiler/java/java_primitive_field.cc
        google/protobuf/compiler/java/java_service.cc
        google/protobuf/compiler/java/java_string_field.cc
        google/protobuf/compiler/python/python_generator.cc
    )
    
    SET(PROTOC_SOURCES google/protobuf/compiler/main.cc)
    
    ADD_TO_GLOBAL_SOURCE_LIST(CMakeLists.txt)

########## Build SQLite library ##########

    ADD_LIBRARY(libsqlite3 STATIC sqlite/sqlite3.c)

    ADD_EXECUTABLE(sqlite3 sqlite/shell.c)
    TARGET_LINK_LIBRARIES(sqlite3 libsqlite3)

    IF (CMAKE_COMPILER_IS_GNUCXX)
        FIND_PACKAGE(Threads)
        TARGET_LINK_LIBRARIES(libsqlite3 dl ${CMAKE_THREAD_LIBS_INIT})
    ENDIF ()

########## Build Protocol Buffers libraries and compiler ##########

    ADD_LIBRARY(libprotobuf STATIC ${LIBPROTOBUF_SOURCES})
    ADD_LIBRARY(libprotoc STATIC ${LIBPROTOC_SOURCES})
    
    ADD_EXECUTABLE(protoc ${PROTOC_SOURCES})
    TARGET_LINK_LIBRARIES(protoc libprotoc libprotobuf)
    
########## Disable warnings for external code compilation ##########

    SET(EXTERNAL_TARGETS libsqlite3 sqlite3 libprotobuf libprotoc protoc)
    IF (CMAKE_COMPILER_IS_GNUCXX)
        SET_TARGET_PROPERTIES(${EXTERNAL_TARGETS} PROPERTIES COMPILE_FLAGS "-w")
    ELSEIF (MSVC)
        SET_TARGET_PROPERTIES(${EXTERNAL_TARGETS} PROPERTIES COMPILE_FLAGS "/W0")
    ENDIF ()

########## Create macro for .proto file compilation ##########

    MACRO(COMPILE_PROTO_FILES GENERATED_SOURCES)
        SET(${GENERATED_SOURCES})
        FOREACH(FILENAME ${ARGN})
            GET_SOURCE_FILE_PROPERTY(FULL_NAME ${FILENAME} LOCATION)
            GET_FILENAME_COMPONENT(FILE_PATH ${FULL_NAME} PATH)
            GET_FILENAME_COMPONENT(BASE_NAME ${FULL_NAME} NAME_WE)
            ADD_CUSTOM_COMMAND(
                OUTPUT
                "${FILE_PATH}/${BASE_NAME}.pb.h"
                "${FILE_PATH}/${BASE_NAME}.pb.cc"
                DEPENDS
                protoc
                "${FULL_NAME}"
                COMMAND
                protoc
                ARGS
                --proto_path="${FILE_PATH}"
                --cpp_out="${FILE_PATH}"
                "${FULL_NAME}"
            )
            LIST(APPEND ${GENERATED_SOURCES} "${FILE_PATH}/${BASE_NAME}.pb.cc")
        ENDFOREACH()
    ENDMACRO()
    
########## Install Eigen headers ##########
    
    INSTALL(DIRECTORY Eigen
        DESTINATION include
        PATTERN "CMakeLists.txt" EXCLUDE
    )
