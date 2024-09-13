cmake_minimum_required(VERSION 3.29)
project(Projeto_Biblioteca C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projeto_Biblioteca
        emprestimo.c
        emprestimo.h
        hora.c
        hora.h
        livros.c
        livros.h
        main.c
        usuarios.c
        usuarios.h)
