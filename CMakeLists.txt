cmake_minimum_required(VERSION 3.10)  # минимальная версия CMake

project(bf_interpreter)                     # имя проекта

set(CMAKE_CXX_STANDARD 17)             # стандарт C++

add_executable(bf_interpreter src/main.cpp)     # собираем исполняемый файл из main.cpp
