cmake_minimum_required(VERSION 3.24)
project(assignment1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(assignment1
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        main.cpp
        Player.cpp
        Player.h
        PlayerDriver.cpp OrdersDriver.cpp Orders.cpp Map.cpp CommandProcessing.cpp Part1Driver.cpp)
