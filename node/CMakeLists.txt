cmake_minimum_required(VERSION 3.10)
# project(SerializePayChanAuth LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

execute_process(
    COMMAND node -p "require('node-addon-api').include"
    OUTPUT_VARIABLE NODE_ADDON_API_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REPLACE "\"" "" NODE_ADDON_API_INCLUDE_DIR ${NODE_ADDON_API_INCLUDE_DIR})

execute_process(
    COMMAND node -p "process.argv[0]"
    OUTPUT_VARIABLE NODE_EXECUTABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(NODE_ROOT ${NODE_EXECUTABLE} DIRECTORY)
set(NODE_API_INCLUDE_DIR "${NODE_ROOT}/../include/node")

add_subdirectory(${CMAKE_SOURCE_DIR}/../core ${CMAKE_BINARY_DIR}/core_build)

add_library(addon SHARED
    addon.cpp
)

target_include_directories(addon
    PRIVATE
        ${NODE_API_INCLUDE_DIR} 
        ${NODE_ADDON_API_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/xahaud/src
)

target_link_libraries(addon
    PRIVATE
    paychan_auth
)

set_target_properties(addon PROPERTIES
    PREFIX ""
    SUFFIX ".node"
)
