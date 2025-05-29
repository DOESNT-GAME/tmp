cmake_minimum_required(VERSION 3.16)

project(echoServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/mytcpserver.cpp
)

set(HEADERS
    include/mytcpserver.h
)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Network)

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)
