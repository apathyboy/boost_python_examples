
# create a module library for the python api

include_directories(${PYTHON_INCLUDE_DIRS})

add_library(testlib MODULE 
    testlib.cpp)

if(WIN32)
    set(BINDING_SUFFIX .pyd)
else()
    set(BINDING_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
    
set_target_properties(testlib
    PROPERTIES 
        PREFIX ""
        SUFFIX "${BINDING_SUFFIX}")

target_link_libraries(testlib
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES})
