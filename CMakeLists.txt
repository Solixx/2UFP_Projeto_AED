cmake_minimum_required(VERSION 3.23)
project(2UFP_Projeto_AED C)

set(CMAKE_C_STANDARD 99)

add_executable(2UFP_Projeto_AED main.c lib_projeto/projeto.c lib_projeto/projeto.h lib_projeto/testes.c lib_projeto/testes.h)
