cmake_minimum_required(VERSION 3.27)
project(Lab2Bag)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2Bag Bag.h ExtendedTest.h ShortTest.h BagIterator.h
        Bag.cpp
        BagIterator.cpp
        ExtendedTest.cpp
        ShortTest.cpp App.cpp)
