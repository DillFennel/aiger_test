cmake_minimum_required(VERSION 2.8) #Check CMake version

project(test_cmake)			# Название проекта 

add_library(aiger aiger.c)	# Создание библиотеки с именем aiger (It can be dimanic or static, de facto static)

add_executable(main func.cpp)	# Создает исполняемый файл с именем main

target_link_libraries(main aiger) #Link program with library
