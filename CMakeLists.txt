cmake_minimum_required(VERSION 3.10)
project(SerializePayChanAuth LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

add_library(paychan_auth STATIC
    PayChan.cpp
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

target_include_directories(paychan_auth
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/xahaud/src
    ${Boost_INCLUDE_DIRS}
)


target_link_libraries(paychan_auth
    PUBLIC
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::thread
    Threads::Threads
    )
add_executable(paychan_main
    main.cpp
)
target_link_libraries(paychan_main
    PRIVATE
    paychan_auth
)