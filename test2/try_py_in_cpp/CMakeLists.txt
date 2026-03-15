project(test_cpp_import_python)
cmake_minimum_required(VERSION 3.5)

find_package(Python3 3.10 REQUIRED COMPONENTS Interpreter Development)

add_executable(test test.cpp)
target_link_libraries(test Python3::Python)