cmake_minimum_required(VERSION 3.10)

project(Image-Filter-Application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(filter 
               main.cpp
               src/filters.cpp
               src/helpers.cpp)


add_compile_options(-fsanitize=asigned-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c++11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow)
