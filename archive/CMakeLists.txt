cmake_minimum_required(VERSION 3.20)
project(ZeroServer)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

add_library(ZeroNetwork network/base.hpp network/network.cpp network/network.hpp network/server.cpp network/server.hpp network/client.cpp network/client.hpp)
target_precompile_headers(ZeroNetwork PRIVATE network/base.hpp)
target_link_libraries(ZeroNetwork pthread)

add_library(ZeroDatabase database/base.hpp database/database.cpp database/database.hpp)
target_precompile_headers(ZeroDatabase PRIVATE database/base.hpp)
target_link_libraries(ZeroDatabase pq)

add_executable(ZeroServer main.cpp)
target_link_libraries(ZeroServer ZeroNetwork ZeroDatabase)
