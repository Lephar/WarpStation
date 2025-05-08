cmake_minimum_required(VERSION 3.27)

project(WarpStation)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.c)

set(SOURCE_COMPILE_OPTIONS -Wall -Wextra)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_compile_options(${PROJECT_NAME} PUBLIC ${SOURCE_COMPILE_OPTIONS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_precompile_headers(${PROJECT_NAME} PUBLIC include/pch.h)
target_link_libraries(${PROJECT_NAME} pthread uuid)
