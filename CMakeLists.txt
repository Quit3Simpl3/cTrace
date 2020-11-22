cmake_minimum_required(VERSION 3.17)
project(spl_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(spl_01
        Agent.h
        Graph.h
        json.hpp
        main.cpp
        Session.h
        Tree.h
        Graph.cpp Agent.cpp Tree.cpp Session.cpp TestersChoice.cpp)
