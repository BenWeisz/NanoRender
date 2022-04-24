cmake_minimum_required(VERSION 3.1)

project("NanoRenderer")
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/out)
