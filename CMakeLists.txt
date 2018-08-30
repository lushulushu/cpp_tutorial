cmake_minimum_required(VERSION 2.8)
project(cpp_tutorial)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

SET(UTILS_SRC
        utils/mutex.cc
        )

add_library(utils STATIC ${UTILS_SRC})

target_link_libraries(utils pthread)

add_executable(pointer pointer/pointer.cc)

add_executable(thread_safety thread_safety/container.cc)

add_executable(vector_pointer vector_pointer/vector_pointer.cc)

target_link_libraries(thread_safety utils)

