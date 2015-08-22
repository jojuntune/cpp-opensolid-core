########## Compile OpenSolidScripting library ##########

    set(OPENSOLID_SCRIPTING_SOURCES
        ScriptEngine.cpp
    )

    if(${BUILD_STATIC_LIBS})
        add_library(OpenSolidScripting STATIC ${OPENSOLID_SCRIPTING_SOURCES})
        set_target_properties(OpenSolidScripting PROPERTIES OUTPUT_NAME OpenSolidScriptingStatic)
    else()
        add_library(OpenSolidScripting SHARED ${OPENSOLID_SCRIPTING_SOURCES})
    endif()
    set_target_properties(OpenSolidScripting PROPERTIES DEBUG_POSTFIX Debug)
    target_link_libraries(OpenSolidScripting wren)

########## Install OpenSolidScripting headers and library ##########

    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION include/OpenSolid
        FILES_MATCHING PATTERN *.hpp
    )
        
    install(
        TARGETS OpenSolidScripting
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
