cmake_minimum_required(VERSION 3.23)
project(2UFP_Projeto_AED C)

set(CMAKE_C_STANDARD 99)

add_executable(2UFP_Projeto_AED main.c pr/projeto.c pr/projeto.h libs_src/lib_util.h libs_src/lib_util.c libs_src/lib_stats.c libs_src/lib_stats.h)
