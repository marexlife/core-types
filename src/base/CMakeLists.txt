cmake_minimum_required(VERSION 3.20)
project(core_types_base)

include(${CMAKE_SOURCE_DIR}/cmake/flags.cmake)

set(COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
    base.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${CORETYPES_FLAGS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)