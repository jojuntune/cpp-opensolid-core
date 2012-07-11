# Generate resource .cpp file
QT4_ADD_RESOURCES(IMAGES_RESOURCE res/images.qrc)

# Collect .ui files
SET(UI_INTERFACE_FILES dlgPointDetails.ui mainWindow.ui)

# Generate ui_XXX.h headers from .ui files
QT4_WRAP_UI(UI_INTERFACE_HEADERS ${UI_INTERFACE_FILES})

# Collect headers to be passed to moc
SET(UI_MOC_HEADERS
    dlgPointDetails.h
    graphItemModel.h
    mainWindow.h
    modelView.h
    nodePropItemModel.h
    treeWidget.h
)
    
# Use moc to generate source files from headers
QT4_WRAP_CPP(UI_MOC_SOURCES ${UI_MOC_HEADERS})

# Collect all other UI source files
SET(UI_SOURCES
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

# Include build directory so ui_XXX.h headers (generated from the .ui files)
# can be found, and the current directory so generated headers can find headers
# in the current directory
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

# Compile and link UI library

ADD_LIBRARY(OpenSolidUI
    ${UI_INTERFACE_HEADERS}
    ${UI_SOURCES}
    ${UI_MOC_SOURCES}
    ${IMAGES_RESOURCE}
)
SET_TARGET_PROPERTIES(OpenSolidUI PROPERTIES DEBUG_POSTFIX "d")

SET(GLOBAL_SOURCE_LIST
    ${GLOBAL_SOURCE_LIST}
    ${UI_MOC_HEADERS}
    ${UI_SOURCES}
    ${STK_SOURCES}
    CMakeLists.txt
    PARENT_SCOPE
)

TARGET_LINK_LIBRARIES(OpenSolidUI ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

# Compile OpenSolid application

ADD_EXECUTABLE(OpenSolid opensolid.cpp)

TARGET_LINK_LIBRARIES(OpenSolid
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    OpenSolidUI
    OpenSolidGraph
    OpenSolidSTK
)
   
# Temporary fix - define 'override' as empty macro for GCC < 4.7
IF(CMAKE_COMPILER_IS_GNUCXX AND GCC_VERSION VERSION_LESS 4.7)
    SET_TARGET_PROPERTIES(
        OpenSolidUI
        OpenSolid
        PROPERTIES
        COMPILE_FLAGS
        "-Doverride="
    )
ENDIF()
    
