
cmake_minimum_required(VERSION 2.8.6)

project(boost_python_examples)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Python_ADDITIONAL_VERSIONS 3.2)

add_definitions(/DBOOST_ALL_NO_LIB)

find_package(Boost 1.49.0 COMPONENTS python thread REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(greet)
add_subdirectory(polymorphism)
add_subdirectory(shell)
add_subdirectory(state_saving)
