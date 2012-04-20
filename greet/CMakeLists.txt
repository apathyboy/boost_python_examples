
# create a static library for the C++ api
set(CPP_SOURCES 
    greet.h
    greet.cpp
)

add_library(greet STATIC ${CPP_SOURCES})

set_target_properties(greet
    PROPERTIES PREFIX "lib"
)

set(BINDING_SOURCES
    greet_binding.cpp
)

# create a module library for the python api

include_directories(${PYTHON_INCLUDE_DIRS})

add_library(greet_bindings SHARED ${BINDING_SOURCES})

if(WIN32)
    set(BINDING_SUFFIX .pyd)
else()
    set(BINDING_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
    
set_target_properties(greet_bindings
    PROPERTIES OUTPUT_NAME greet
    PREFIX ""
    SUFFIX "${BINDING_SUFFIX}"
)

target_link_libraries(greet_bindings
    greet
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)
