cmake_minimum_required(VERSION 3.10)
project(Lab_OS_CrossPlatform CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

if(WIN32)
    set(OS_WRAPPER src/os_wrapper_win.cpp)
else()
    set(OS_WRAPPER src/os_wrapper_posix.cpp)
endif()

add_library(os_wrapper ${OS_WRAPPER})

add_executable(child src/child.cpp)
add_executable(parent src/parent.cpp)

target_link_libraries(child PRIVATE os_wrapper)
target_link_libraries(parent PRIVATE os_wrapper)

set_target_properties(child parent PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_command(
    TARGET parent POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/input.txt
            ${CMAKE_BINARY_DIR}/bin/input.txt
)
