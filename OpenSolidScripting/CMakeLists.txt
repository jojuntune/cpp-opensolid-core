ADD_LIBRARY(OpenSolidScripting SHARED Script.cpp)

TARGET_LINK_LIBRARIES(
    OpenSolidScripting
    OpenSolid
    OpenSolidPython
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
    
INSTALL(
    TARGETS OpenSolidScripting
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

ADD_CXXTEST(Script.tests Script.tests.hpp OpenSolidScripting OpenSolid)
