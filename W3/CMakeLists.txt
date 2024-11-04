# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(w3 VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_executable(w3 src/main.cpp)

option(ENABLE_INFO "Enable info mode" ON)
if(ENABLE_INFO)
    target_compile_definitions(w3 PRIVATE INFO_MODE)
endif()