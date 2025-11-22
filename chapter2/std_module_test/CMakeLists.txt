cmake_minimum_required(VERSION 3.30)
project(std_module_test CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable C++ modules scanning


add_executable(std_module_test main.cpp)
