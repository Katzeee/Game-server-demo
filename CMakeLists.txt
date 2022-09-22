# pre settings

cmake_minimum_required(VERSION 3.14)
project(game-server)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED 14) 
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -Wall -Wno-deprecated -Werror -Wno-unused-function -D_GLIBCXX_DEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# 3rd library

find_package(Protobuf REQUIRED)
find_package(CURL REQUIRED)
set(link_libs ${CURL_LIBRARIES} ${PROTOBUF_LIBRARIES})

# source files 

aux_source_directory(src LIB_SRC)
file(GLOB proto_files CONFIG_DEPENDS src/protobuf/*.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${proto_files})


add_library(libserver OBJECT ${LIB_SRC} ${PROTO_SRCS})
target_link_libraries(libserver ${link_libs})


# tests

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

aux_source_directory(test/message_list_test MSG_TEST_SRC)
add_executable(msg_list_test ${MSG_TEST_SRC})
add_dependencies(msg_list_test libserver)
target_link_libraries(msg_list_test libserver)