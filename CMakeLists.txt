# pre settings

cmake_minimum_required(VERSION 3.14)
project(game-server)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED 17) 
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -Wall -Wno-deprecated -Werror -Wno-unused-function -O0 -D_GLIBCXX_DEBUG -fsanitize=address")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# 3rd library

find_package(Protobuf REQUIRED)
find_package(CURL REQUIRED)
#find_package(jsoncpp REQUIRED)
set(link_libs ${CURL_LIBRARIES} ${PROTOBUF_LIBRARIES} jsoncpp)

# source files 

aux_source_directory(src/lib LIB_SRC)
file(GLOB proto_files CONFIG_DEPENDS src/protobuf/*.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${proto_files})

aux_source_directory(src/ecslib LIB_ECS_SRC)
aux_source_directory(src/robot ROBOT_SRC)
message(STATUS ${ROBOT_SRC})


add_library(libserver OBJECT ${LIB_SRC} ${PROTO_SRCS})
target_link_libraries(libserver ${link_libs})

add_library(ecslibserver OBJECT ${LIB_ECS_SRC} ${PROTO_SRCS} ${ROBOT_SRC})
target_link_libraries(ecslibserver ${link_libs})


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

add_executable(thread_test test/thread_test.cpp)
add_dependencies(thread_test libserver)
target_link_libraries(thread_test libserver)

add_executable(msg_list_test test/TestMsgHandler.cpp)
add_dependencies(msg_list_test libserver)
target_link_libraries(msg_list_test libserver)

add_executable(robot test/robot.cpp)
add_dependencies(robot libserver)
target_link_libraries(robot libserver)

add_executable(objectpool_test test/objectpool_test.cpp)
add_dependencies(objectpool_test ecslibserver)
target_link_libraries(objectpool_test ecslibserver)

add_executable(entitysystem_test test/entitysystem_test.cpp)
add_dependencies(entitysystem_test ecslibserver)
target_link_libraries(entitysystem_test ecslibserver)

add_executable(newlistener_test test/newlistener_test.cpp)
add_dependencies(newlistener_test ecslibserver)
target_link_libraries(newlistener_test ecslibserver)

add_executable(console_test test/console_test.cpp)
add_dependencies(console_test ecslibserver)
target_link_libraries(console_test ecslibserver)

add_executable(common_test test/common_test.cpp)
add_dependencies(common_test ecslibserver)
target_link_libraries(common_test ecslibserver)

add_executable(accountverifyserver test/accountverifyserver.cpp)
add_dependencies(accountverifyserver ecslibserver)
target_link_libraries(accountverifyserver ecslibserver)

add_executable(accountverifyclient test/accountverifyclient.cpp)
add_dependencies(accountverifyclient ecslibserver)
target_link_libraries(accountverifyclient ecslibserver)