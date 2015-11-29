cmake_minimum_required(VERSION 2.8)
project(PingPongProtocol)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
        src/Helper/ArgsParser.cpp
        src/Helper/ArgsParser.hpp
        src/Helper/Logger.cpp
        src/Helper/Logger.hpp
        src/Message.cpp
        src/Message.hpp
        src/Peer/Peer.cpp
        src/Peer/Peer.hpp
        src/Peer/Peer_p.cpp
        src/Peer/Peer_p.hpp
        src/Peer/Peer_pp.cpp
        src/Peer/Peer_pp.hpp
        src/TopologyGen.cpp
        src/TopologyGen.hpp)

find_package(LibConfig++ REQUIRED)
include_directories(${LIBCONFIG++_INCLUDE_DIR})
set(LIBS ${LIBS} ${LIBCONFIG++_LIBRARY})

add_executable(PingPongProtocol_v1 ${SOURCE_FILES} src/main.cpp)
add_executable(PingPongProtocol_v2 ${SOURCE_FILES} src/main.cpp)
add_executable(PingPongProtocol_v3 ${SOURCE_FILES} src/main.cpp)
#add_executable(PingPongStatistics ${SOURCE_FILES} main_statistics.cpp)

target_compile_definitions(PingPongProtocol_v1 PUBLIC "V1")
target_compile_definitions(PingPongProtocol_v2 PUBLIC "V2")
target_compile_definitions(PingPongProtocol_v3 PUBLIC "V3")

target_link_libraries(PingPongProtocol_v1 ${LIBS})
target_link_libraries(PingPongProtocol_v2 ${LIBS})
target_link_libraries(PingPongProtocol_v3 ${LIBS})
