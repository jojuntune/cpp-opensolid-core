# Generate resource .cpp file
QT4_ADD_RESOURCES(IMAGES_RESOURCE "${OpenSolid}/UI/res/images.qrc")

# Collect .ui files
SET(UI_INTERFACE_FILES
    "${OpenSolid}/UI/dlgPointDetails.ui"
    "${OpenSolid}/UI/mainWindow.ui"
)

# Generate ui_XXX.h headers from .ui files
QT4_WRAP_UI(UI_INTERFACE_HEADERS ${UI_INTERFACE_FILES})

# Collect headers to be passed to moc
SET(UI_MOC_HEADERS
    "${OpenSolid}/UI/dlgPointDetails.h"
    "${OpenSolid}/UI/graphItemModel.h"
    "${OpenSolid}/UI/mainWindow.h"
    "${OpenSolid}/UI/modelView.h"
    "${OpenSolid}/UI/nodePropItemModel.h"
    "${OpenSolid}/UI/treeWidget.h"
)
    
# Use moc to generate source files from headers
QT4_WRAP_CPP(UI_MOC_SOURCES ${UI_MOC_HEADERS})

# Collect all other UI source files
SET(UI_SOURCES
    "${OpenSolid}/UI/camera.cpp"
    "${OpenSolid}/UI/cameraModelView.cpp"
    "${OpenSolid}/UI/cameraFirstPerson.cpp"
    "${OpenSolid}/UI/dlgPointDetails.cpp"
    "${OpenSolid}/UI/graphItemModel.cpp"
    "${OpenSolid}/UI/mainWindow.cpp"
    "${OpenSolid}/UI/modelView.cpp"
    "${OpenSolid}/UI/nodePropItemModel.cpp"
    "${OpenSolid}/UI/renderTarget.cpp"
    "${OpenSolid}/UI/treeWidget.cpp"
    "${OpenSolid}/UI/projectRenderTarget.cpp"
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

SET(GLOBAL_SOURCE_LIST
    ${GLOBAL_SOURCE_LIST}
    ${UI_MOC_HEADERS}
    ${UI_SOURCES}
    ${STK_SOURCES}
    "${OpenSolid}/UI/CMakeLists.txt"
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
