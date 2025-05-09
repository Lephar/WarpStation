cmake_minimum_required(VERSION 3.27)

project(WarpStation)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES     src/*.c)

set(SOURCE_COMPILE_OPTIONS -Wall -Wextra)

set(CONFIG_INPUT  ${PROJECT_SOURCE_DIR}/data/config.txt)
set(CONFIG_OUTPUT ${PROJECT_BINARY_DIR}/data/config.txt)

add_custom_command(
    OUTPUT  ${CONFIG_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E copy ${CONFIG_INPUT} ${CONFIG_OUTPUT}
    DEPENDS ${CONFIG_INPUT}
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${CONFIG_INPUT} ${CONFIG_OUTPUT})
target_compile_options(${PROJECT_NAME} PUBLIC ${SOURCE_COMPILE_OPTIONS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_precompile_headers(${PROJECT_NAME} PUBLIC include/pch.h)
target_link_libraries(${PROJECT_NAME} pthread uuid)
