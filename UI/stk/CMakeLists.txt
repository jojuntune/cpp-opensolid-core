file(GLOB STK_SOURCES *.cpp)
add_library(opensolid_stk ${STK_SOURCES})
SET_TARGET_PROPERTIES(opensolid_stk PROPERTIES DEBUG_POSTFIX _debug)
TARGET_LINK_LIBRARIES(opensolid_stk ${QT_LIBRARIES})
