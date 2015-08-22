########## Set up Wren source tree ##########

    externalproject_add(
        wren_sources
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}
        URL ${CMAKE_CURRENT_SOURCE_DIR}/wren.tar.gz
        URL_MD5 ecec8a571db5354e66bbcd6da8c7fe89
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    set(WREN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/src/wren_sources/src)
    set(WREN_INCLUDE_DIR ${WREN_ROOT}/include)
    
    # Set WREN_INCLUDE_DIR in external/ directory (will then be passed up to root)
    set(WREN_INCLUDE_DIR ${WREN_INCLUDE_DIR} PARENT_SCOPE)

    # Include WREN_INCLUDE_DIR to allow compilation of Wren code
    include_directories(${WREN_INCLUDE_DIR})

########## Build Wren library ##########

    set(WREN_SOURCES
        ${WREN_ROOT}/vm/wren_compiler.c
        ${WREN_ROOT}/vm/wren_core.c
        ${WREN_ROOT}/vm/wren_debug.c
        ${WREN_ROOT}/vm/wren_io.c
        ${WREN_ROOT}/vm/wren_meta.c
        ${WREN_ROOT}/vm/wren_utils.c
        ${WREN_ROOT}/vm/wren_value.c
        ${WREN_ROOT}/vm/wren_vm.c
    )

    set_source_files_properties(${WREN_SOURCES} PROPERTIES GENERATED TRUE)

    add_library(wren STATIC ${WREN_SOURCES})
    set_target_properties(wren PROPERTIES DEBUG_POSTFIX _debug)
    add_dependencies(wren wren_sources)
