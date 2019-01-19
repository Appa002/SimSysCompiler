cmake_minimum_required(VERSION 3.10)
project(SimSysCompiler)

set(CMAKE_CXX_STANDARD 17)

include_directories("Source" "Data")

file(GLOB_RECURSE Classes "./Source/*")
file(GLOB Standalones "./Data/*")


# Add test cpp file
add_executable(SimSysCompiler main.cpp ${Classes} ${Standalones})
add_subdirectory(./tests)