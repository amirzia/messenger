cmake_minimum_required(VERSION 3.14)
project(messanger)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS locale)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message("-- Boost found: ${Boost_VERSION_STRING}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_subdirectory(src)