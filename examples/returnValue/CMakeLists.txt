cmake_minimum_required(VERSION 2.8)

project(returnValue CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

include(EnableCXX11.cmake)

find_package(FutureSynchronizerLibrary REQUIRED)

file(GLOB src
    main.cpp)
    
add_executable(${PROJECT_NAME} ${src})