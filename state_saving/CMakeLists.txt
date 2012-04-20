
# create a module library for the python api

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(state_saving 
    state_saving.cpp)

target_link_libraries(state_saving
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)

add_library(TEST1 SHARED TEST1.cpp)

if(WIN32)
    set(BINDING_SUFFIX .pyd)
else()
    set(BINDING_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
    
set_target_properties(TEST1
    PROPERTIES OUTPUT_NAME TEST1
    PREFIX ""
    SUFFIX "${BINDING_SUFFIX}"
)

target_link_libraries(TEST1
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)