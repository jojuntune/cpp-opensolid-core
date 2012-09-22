########## Compile Python extension module ##########
    
    file(GLOB MODULE_SOURCES detail/*.cpp)
    add_library(opensolid_python_module SHARED ${MODULE_SOURCES})
    set_target_properties(opensolid_python_module PROPERTIES PREFIX "" OUTPUT_NAME opensolid)
    set_target_properties(opensolid_python_module PROPERTIES DEBUG_POSTFIX _debug)
    if(WIN32)
        set_target_properties(opensolid_python_module PROPERTIES SUFFIX ".pyd")
    endif()
    target_link_libraries(
        opensolid_python_module
        opensolid_core
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Compile OpenSolidPython library ##########
    
    add_library(opensolid_python SHARED PythonEnvironment.cpp)
    set_target_properties(opensolid_python PROPERTIES DEBUG_POSTFIX _debug)
    target_link_libraries(
        opensolid_python
        opensolid_core
        opensolid_python_module
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Install headers ##########
    
    install(DIRECTORY . DESTINATION include/opensolid FILES_MATCHING PATTERN *.hpp)
    
########## Install libraries ##########
        
    install(
        TARGETS opensolid_python
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )

    # Get site packages directory
    execute_process(
        COMMAND "${PYTHON_EXECUTABLE}"
        -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Install Python extension module
    install(TARGETS opensolid_python_module DESTINATION ${PYTHON_SITE_PACKAGES})

########## Add files to global source list ##########

    add_to_global_source_list(* detail/*)
