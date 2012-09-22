macro(create_source_groups)
    get_property(SOURCE_LIST GLOBAL PROPERTY GLOBAL_SOURCE_LIST)
    
    # Add dummy ALL_SOURCES target to include all source files
    add_library(ALL_SOURCES EXCLUDE_FROM_ALL ${SOURCE_LIST})

    # Get list of all unique directory paths
    set(PATH_LIST)
    foreach(SOURCE_FILE ${SOURCE_LIST})
        get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
        list(APPEND PATH_LIST ${SOURCE_PATH})
    endforeach()
    list(SORT PATH_LIST)
    list(REMOVE_DUPLICATES PATH_LIST)
    
    # Include subdirectory includes so autocompletion works properly within ALL_SOURCES target
    foreach(UNIQUE_PATH ${PATH_LIST})
        if(EXISTS ${UNIQUE_PATH}/CMakeLists.txt)
            get_directory_property(SUBDIR_INCLUDES DIRECTORY "${UNIQUE_PATH}" INCLUDE_DIRECTORIES)
            include_directories(${SUBDIR_INCLUDES})
        endif()
    endforeach()

    # Set up source groups
    get_filename_component(PARENT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
    foreach(UNIQUE_PATH ${PATH_LIST})
        # Scan through all source files to find those contained within the current subdirectory
        set(CONTAINED_SOURCES)
        foreach(SOURCE_FILE ${SOURCE_LIST})
            get_filename_component(SOURCE_PATH ${SOURCE_FILE} PATH)
            if (${SOURCE_PATH} STREQUAL ${UNIQUE_PATH})
                list(APPEND CONTAINED_SOURCES ${SOURCE_FILE})
            endif()
        endforeach()
        # Generate group name from subdirectory path
        string(REPLACE "${PARENT_DIRECTORY}" "" STRIPPED_PATH ${UNIQUE_PATH})
        string(REGEX REPLACE "/" "\\\\" GROUP_NAME ${STRIPPED_PATH})
        # Create source group
        source_group(${GROUP_NAME} FILES ${CONTAINED_SOURCES})
    endforeach()
endmacro()

macro(add_to_global_source_list)
    foreach(GLOB_EXPRESSION ${ARGN})
        file(GLOB GLOB_RESULTS ${GLOB_EXPRESSION})
        foreach(SOURCE_PATH ${GLOB_RESULTS})
            get_source_file_property(ABSOLUTE_PATH ${SOURCE_PATH} LOCATION)
            if(NOT IS_DIRECTORY ${ABSOLUTE_PATH})
                set_property(GLOBAL APPEND PROPERTY GLOBAL_SOURCE_LIST ${ABSOLUTE_PATH})
            endif()
        endforeach()
    endforeach()
endmacro()
