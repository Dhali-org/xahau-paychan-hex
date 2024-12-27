cmake_minimum_required(VERSION 3.10)
project(SerializePayChanAuth LANGUAGES CXX)

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

find_package(pybind11 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

add_library(paychan_auth STATIC
    PayChan.hpp
    xahaud/src/ripple/basics/impl/IOUAmount.cpp
    xahaud/src/ripple/basics/impl/contract.cpp
    xahaud/src/ripple/basics/impl/Log.cpp
    xahaud/src/ripple/basics/impl/Number.cpp
    xahaud/src/ripple/protocol/impl/AccountID.cpp
    xahaud/src/ripple/protocol/impl/UintTypes.cpp
    xahaud/src/ripple/protocol/impl/Serializer.cpp
    xahaud/src/ripple/protocol/impl/digest.cpp
    xahaud/src/ripple/beast/utility/src/beast_Journal.cpp
    xahaud/src/ripple/protocol/impl/tokens.cpp
    xahaud/src/ripple/beast/hash/impl/xxhash.cpp
)

set_property(TARGET paychan_auth PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(paychan_auth
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/xahaud/src
        ${Boost_INCLUDE_DIRS}
        ${NODE_ADDON_API_INCLUDE_DIR}
        ${NODE_API_INCLUDE_DIR}
)

message(${NODE_ADDON_API_INCLUDE_DIR})
message(${NODE_API_INCLUDE_DIR})

target_link_libraries(paychan_auth
    PUBLIC
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::thread
    Threads::Threads
)

add_library(addon MODULE
    src/addon.cpp
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

pybind11_add_module(paychan_python src/pybind11_wrapper.cpp)

target_include_directories(paychan_python
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/xahaud/src
)

target_link_libraries(paychan_python
    PRIVATE
    paychan_auth
)
