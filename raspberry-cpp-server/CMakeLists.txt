cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")
project(rpi-cpp-server)
add_subdirectory(proto)
target_link_libraries(main )

include_directories(include)


#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cc")

add_executable(rpiserver ${SOURCES})
ADD_SUBDIRECTORY(proto)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
TARGET_LINK_LIBRARIES(main proto ${PROTOBUF_LIBRARY})
