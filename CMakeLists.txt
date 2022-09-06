cmake_minimum_required(VERSION 3.14)
project(game-server)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED 14) 
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -Wall -Wno-deprecated -Werror -Wno-unused-function")

aux_source_directory(src LIB_SRC)
add_library(libserver STATIC ${LIB_SRC})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(server test/server.cpp)
add_executable(client test/client.cpp)
add_dependencies(client libserver)
target_link_libraries(client libserver)

add_executable(network test/networkclasstest.cpp)
add_dependencies(network libserver)
target_link_libraries(network libserver)
