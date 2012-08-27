######### Build STK and graph libraries ##########

    add_subdirectory(stk)
    include_directories(stk)
    
    add_subdirectory(graph)
    include_directories(graph)
    
######### Perform Qt preprocessing ##########

    # Generate resource .cpp file
    qt4_add_resources(IMAGES_RESOURCE res/images.qrc)

    # Collect .ui files
    set(UI_INTERFACE_FILES dlgPointDetails.ui mainWindow.ui)

    # Generate ui_XXX.h headers from .ui files
    qt4_wrap_ui(UI_INTERFACE_HEADERS ${UI_INTERFACE_FILES})

    # Collect headers to be passed to moc
    set(
        UI_MOC_HEADERS
        dlgPointDetails.h
        graphItemModel.h
        mainWindow.h
        modelView.h
        nodePropItemModel.h
        treeWidget.h
    )
    
    # Use moc to generate source files from headers
    qt4_wrap_cpp(UI_MOC_SOURCES ${UI_MOC_HEADERS})

    # Include build directory so ui_XXX.h headers (generated from the .ui files)
    # can be found, and the current directory so generated headers can find headers
    # in the current directory
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

########## Build UI library ##########

    set(
        UI_SOURCES
        camera.cpp
        cameraModelView.cpp
        cameraFirstPerson.cpp
        dlgPointDetails.cpp
        graphItemModel.cpp
        mainWindow.cpp
        modelView.cpp
        nodePropItemModel.cpp
        renderTarget.cpp
        treeWidget.cpp
        projectRenderTarget.cpp
    )
    
    add_library(
        opensolid_ui
        ${UI_INTERFACE_HEADERS}
        ${UI_SOURCES}
        ${UI_MOC_SOURCES}
        ${IMAGES_RESOURCE}
    )
    
    set_target_properties(opensolid_ui PROPERTIES DEBUG_POSTFIX _debug)
    
    add_to_global_source_list(
        ${UI_MOC_HEADERS}
        ${UI_SOURCES}
        ${STK_SOURCES}
        CMakeLists.txt
    )
    
    target_link_libraries(opensolid_ui ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

########## Compile OpenSolid application ##########

    add_executable(opensolid opensolid.cpp)
    
    target_link_libraries(
        opensolid
        ${QT_LIBRARIES}
        ${OPENGL_LIBRARIES}
        opensolid_ui
        opensolid_graph
        opensolid_stk
    )
    
