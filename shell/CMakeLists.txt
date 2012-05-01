
# create a module library for the python api

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(shell 
    shell.cpp)

target_link_libraries(shell
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)
