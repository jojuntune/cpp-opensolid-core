########## Compile Python extension module ##########
    
    file(GLOB MODULE_SOURCES detail/*.cpp)
    add_library(python_module SHARED ${MODULE_SOURCES})
    set_target_properties(python_module PROPERTIES PREFIX "" OUTPUT_NAME opensolid)
    set_target_properties(python_module PROPERTIES DEBUG_POSTFIX d)
    if(WIN32)
        set_target_properties(python_module PROPERTIES SUFFIX ".pyd")
    endif()
    target_link_libraries(python_module OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
########## Compile OpenSolidPython library ##########
    
    add_library(OpenSolidPython SHARED PythonEnvironment.cpp)
    set_target_properties(OpenSolidPython PROPERTIES DEBUG_POSTFIX d)
    target_link_libraries(
        OpenSolidPython
        OpenSolidCore
        python_module
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
    )
    
########## Install OpenSolidPython library ##########
        
    install(
        TARGETS OpenSolidPython
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
    install(TARGETS python_module DESTINATION ${PYTHON_SITE_PACKAGES})

########## Add files to global source list ##########

    add_to_global_source_list(* detail/*)
