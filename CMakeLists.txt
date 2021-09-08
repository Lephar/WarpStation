cmake_minimum_required(VERSION 3.20)
project(ZeroServer)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

add_library(ZeroNetwork network/base.hpp network/network.cpp network/network.hpp network/server.cpp network/server.hpp)
target_precompile_headers(ZeroNetwork PRIVATE network/base.hpp)
target_link_libraries(ZeroNetwork pthread)

add_executable(ZeroServer main.cpp)
target_link_libraries(ZeroServer ZeroNetwork)
