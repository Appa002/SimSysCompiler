cmake_minimum_required(VERSION 3.10)
project(SimSysCompiler)

set(CMAKE_CXX_STANDARD 17)

include_directories("./Classes" "./Standalone")

file(GLOB_RECURSE  Classes "./Classes/*")
file(GLOB Standalones "./Standalone/*")

add_executable(SimSysCompiler main.cpp ${Classes} ${Standalones})
add_subdirectory(./tests)