cmake_minimum_required(VERSION 3.14)
project(game-server)
aux_source_directory(. LIB_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(server server.cpp)
add_executable(client client.cpp)
