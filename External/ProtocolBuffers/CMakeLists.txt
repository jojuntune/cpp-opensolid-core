########## Set up protobuf source tree ##########

    externalproject_add(
        protobuf_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/protobuf-2.5.0.tar.gz
        URL_MD5 b751f772bdeb2812a2a8e7202bf1dae8
        PATCH_COMMAND
        ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/patch.cmake
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    set(PROTOBUF_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/protobuf_sources/src)
    
    # Set PROTOBUF_ROOT in external/ directory (will then be passed up to root)
    set(PROTOBUF_ROOT ${PROTOBUF_ROOT} PARENT_SCOPE)

    # Include PROTOBUF_ROOT to allow compilation of protobuf code
    include_directories(${PROTOBUF_ROOT})

########## Build protobuf library ##########

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(PROTOBUF_ATOMIC_OPS_SOURCE_FILE
            "${PROTOBUF_ROOT}/google/protobuf/stubs/atomicops_internals_x86_msvc.cc"
        )
    elseif(APPLE)
        set(PROTOBUF_ATOMIC_OPS_SOURCE_FILE
            "${PROTOBUF_ROOT}/google/protobuf/stubs/atomicops_internals_macosx.cc"
        )
    else()
        set(PROTOBUF_ATOMIC_OPS_SOURCE_FILE
            "${PROTOBUF_ROOT}/google/protobuf/stubs/atomicops_internals_x86_gcc.cc"
        )
    endif()
    set(PROTOBUF_SOURCES
        "${PROTOBUF_ROOT}/google/protobuf/descriptor.cc"
        "${PROTOBUF_ROOT}/google/protobuf/descriptor.pb.cc"
        "${PROTOBUF_ROOT}/google/protobuf/descriptor_database.cc"
        "${PROTOBUF_ROOT}/google/protobuf/dynamic_message.cc"
        "${PROTOBUF_ROOT}/google/protobuf/extension_set.cc"
        "${PROTOBUF_ROOT}/google/protobuf/extension_set_heavy.cc"
        "${PROTOBUF_ROOT}/google/protobuf/generated_message_reflection.cc"
        "${PROTOBUF_ROOT}/google/protobuf/generated_message_util.cc"
        "${PROTOBUF_ROOT}/google/protobuf/message.cc"
        "${PROTOBUF_ROOT}/google/protobuf/message_lite.cc"
        "${PROTOBUF_ROOT}/google/protobuf/reflection_ops.cc"
        "${PROTOBUF_ROOT}/google/protobuf/repeated_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/service.cc"
        "${PROTOBUF_ROOT}/google/protobuf/text_format.cc"
        "${PROTOBUF_ROOT}/google/protobuf/unknown_field_set.cc"
        "${PROTOBUF_ROOT}/google/protobuf/wire_format.cc"
        "${PROTOBUF_ROOT}/google/protobuf/wire_format_lite.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/coded_stream.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/gzip_stream.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/printer.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/tokenizer.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/zero_copy_stream.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/zero_copy_stream_impl.cc"
        "${PROTOBUF_ROOT}/google/protobuf/io/zero_copy_stream_impl_lite.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/common.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/once.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/stringprintf.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/structurally_valid.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/strutil.cc"
        "${PROTOBUF_ROOT}/google/protobuf/stubs/substitute.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/importer.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/parser.cc"
        "${PROTOBUF_ATOMIC_OPS_SOURCE_FILE}"
    )

    set_source_files_properties(${PROTOBUF_SOURCES} PROPERTIES GENERATED TRUE)
    add_library(protobuf STATIC ${PROTOBUF_SOURCES})
    set_target_properties(protobuf PROPERTIES DEBUG_POSTFIX _debug)
    set_target_properties(protobuf PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
    add_dependencies(protobuf protobuf_sources)

########## Build protoc compiler ##########

    SET(PROTOC_SOURCES
        "${PROTOBUF_ROOT}/google/protobuf/compiler/main.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/code_generator.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/command_line_interface.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/plugin.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/plugin.pb.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/subprocess.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/zip_writer.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_enum.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_enum_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_extension.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_file.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_generator.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_helpers.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_message.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_message_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_primitive_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_service.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/cpp/cpp_string_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_doc_comment.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_enum.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_enum_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_extension.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_file.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_generator.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_helpers.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_message.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_message_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_primitive_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_service.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/java/java_string_field.cc"
        "${PROTOBUF_ROOT}/google/protobuf/compiler/python/python_generator.cc"
    )
    set_source_files_properties(${PROTOC_SOURCES} PROPERTIES GENERATED TRUE)
    add_executable(protoc ${PROTOC_SOURCES})
    set_target_properties(protoc PROPERTIES COMPILE_FLAGS ${DISABLE_WARNINGS_FLAG})
    add_dependencies(protoc protoc_sources)
    target_link_libraries(protoc protobuf)
    
########## Add files to global source list ##########

    add_to_global_source_list(*)
