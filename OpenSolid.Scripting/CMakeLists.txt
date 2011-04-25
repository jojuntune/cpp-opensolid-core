ADD_LIBRARY(opensolid_scripting SHARED Script.cpp)

TARGET_LINK_LIBRARIES(
    opensolid_scripting
    opensolid
    opensolid_python
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
    
INSTALL(
    TARGETS opensolid_scripting
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

ADD_CXXTEST(Script.tests Script.tests.hpp opensolid_scripting opensolid)
