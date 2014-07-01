########## Compile Python extension module ##########
    
    file(
        GLOB
        EXTENSION_SOURCES
        PythonExtension.cpp
        repr.cpp
        PythonExtension/bindDouble.cpp
        PythonExtension/bindError.cpp
        PythonExtension/bindInterval.cpp
        PythonExtension/bindZero.cpp
    )

    add_library(python_extension SHARED ${EXTENSION_SOURCES})
    set_target_properties(python_extension PROPERTIES PREFIX "" OUTPUT_NAME opensolid)
    set_target_properties(python_extension PROPERTIES DEBUG_POSTFIX _debug)
    if(WIN32)
        set_target_properties(python_extension PROPERTIES SUFFIX ".pyd")
    endif()
    target_link_libraries(python_extension OpenSolidCore ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    
########## Compile OpenSolidPython library ##########
    
    # add_library(OpenSolidPython SHARED PythonEnvironment.cpp)
    # set_target_properties(OpenSolidPython PROPERTIES DEBUG_POSTFIX Debug)
    # target_link_libraries(
    #     OpenSolidPython
    #     OpenSolidCore
    #     python_extension
    #     ${Boost_LIBRARIES}
    #     ${PYTHON_LIBRARIES}
    # )

########## Install Python extension module ##########

    # Get site packages directory
    execute_process(
        COMMAND "${PYTHON_EXECUTABLE}"
        -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Install Python extension module
    install(TARGETS python_extension DESTINATION ${PYTHON_SITE_PACKAGES})
    
########## Install OpenSolidPython headers and library ##########

    # install(
    #     DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    #     DESTINATION include/OpenSolid
    #     FILES_MATCHING PATTERN *.hpp
    # )
        
    # install(
    #     TARGETS OpenSolidPython
    #     RUNTIME DESTINATION bin
    #     LIBRARY DESTINATION lib
    #     ARCHIVE DESTINATION lib
    # )

########## Add files to global source list ##########

    add_to_global_source_list(* PythonExtension/*)
