cmake_minimum_required(VERSION 3.5)

project(hammingCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( hammingCode main.cpp c_hamming/src/c_hamming.cpp )

include_directories( c_hamming/h/ )
