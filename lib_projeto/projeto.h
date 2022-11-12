//
// Created by pc on 11/11/2022.
//

#ifndef INC_2UFP_PROJETO_AED_PROJETO_H
#define INC_2UFP_PROJETO_AED_PROJETO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

int bipolar_number(char *text);

void print_bipolar_numbers(int k);

char* find_mul_bipolar_number(char *k);

int hist(char* num, int histo[]);

int RL_V1(char* num, int runLess[]);

int RL_V2(char* num, int runLess[]);

void cliente0();
void cliente1();
void cliente2();
void cliente3();

void main_lib_projeto();

#endif //INC_2UFP_PROJETO_AED_PROJETO_H
