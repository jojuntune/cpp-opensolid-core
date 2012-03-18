macro(create_source_groups)
    # Add dummy ALL_SOURCES target to include all source files
    add_library(ALL_SOURCES EXCLUDE_FROM_ALL ${ARGN})

    # Get list of all unique directory paths
    set(PATH_LIST)
    foreach(SOURCE_FILE ${ARGN})
        get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
        list(APPEND PATH_LIST ${SOURCE_PATH})
    endforeach()
    list(SORT PATH_LIST)
    list(REMOVE_DUPLICATES PATH_LIST)
    
    # Include subdirectory includes so autocompletion works properly within ALL_SOURCES target
    foreach(GROUP_PATH ${PATH_LIST})
        if(EXISTS ${GROUP_PATH}/CMakeLists.txt)
            get_directory_property(SUBDIR_INCLUDES DIRECTORY "${GROUP_PATH}" INCLUDE_DIRECTORIES)
            include_directories(${SUBDIR_INCLUDES})
        endif()
    endforeach()

    # Set up source groups
    get_filename_component(PARENT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
    foreach(GROUP_PATH ${PATH_LIST})
        # Scan through all source files to find those contained within the current subdirectory
        set(CONTAINED_SOURCES)
        foreach(SOURCE_FILE ${ARGN})
            get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
            if (${SOURCE_PATH} STREQUAL ${GROUP_PATH})
                list(APPEND CONTAINED_SOURCES ${SOURCE_FILE})
            endif()
        endforeach()
        # Generate group name from subdirectory path
        string(REPLACE "${PARENT_DIRECTORY}" "" STRIPPED_PATH ${GROUP_PATH})
        string(REGEX REPLACE "/" "\\\\" GROUP_NAME ${STRIPPED_PATH})
        # Create source group
        source_group(${GROUP_NAME} FILES ${CONTAINED_SOURCES})
    endforeach()
endmacro()
