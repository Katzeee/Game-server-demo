cmake_minimum_required(VERSION 3.14)
project(game-server)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED 14) 
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -Wall -Wno-deprecated -Werror -Wno-unused-function -D_GLIBCXX_DEBUG -lprotobuf")

aux_source_directory(src LIB_SRC)
aux_source_directory(src/protobuf LIB_SRC)
add_library(libserver OBJECT ${LIB_SRC})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(server test/server.cpp)

add_executable(client test/client.cpp)
add_dependencies(client libserver)
target_link_libraries(client libserver)

add_executable(buffertest test/buffer_test.cpp)
add_dependencies(buffertest libserver)
target_link_libraries(buffertest libserver)

add_executable(network_listen test/network_listen_test.cpp)
add_dependencies(network_listen libserver)
target_link_libraries(network_listen libserver)

add_executable(network_conn test/network_connect_test.cpp)
add_dependencies(network_conn libserver)
target_link_libraries(network_conn libserver)


add_executable(singleton_test test/singleton_test.cpp)
add_dependencies(singleton_test libserver)
target_link_libraries(singleton_test libserver)

add_executable(serverapp_test test/serverapp_test.cpp)
add_dependencies(serverapp_test libserver)
target_link_libraries(serverapp_test libserver)

add_executable(thread_test test/thread_test.cpp)
add_dependencies(thread_test libserver)
target_link_libraries(thread_test libserver)