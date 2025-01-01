cmake_minimum_required(VERSION 3.10)
project(SerializePayChanAuth LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/../core ${CMAKE_BINARY_DIR}/core_build)

pybind11_add_module(paychan_python pybind11_wrapper.cpp)

target_link_libraries(paychan_python
    PRIVATE
    paychan_auth
)
