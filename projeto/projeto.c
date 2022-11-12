//
// Created by pc on 11/11/2022.
//

#include "projeto.h"

void main_projeto(){

    //cliente0();
    cliente1();
    //cliente2();
    //cliente3();
}

void cliente0(){
    char t[] = "2211";

    printf("%d\n", bipolar_number(t));
}

void cliente1(){
    int k = 4;
    int n[k];

    print_bipolar_numbers(k);
}

void cliente2(){
    char t[] = "77555";
    int histo[10];

    if(bipolar_number(t) == 0){
        hist(t, histo);
        for (int i = 0; i < 10; ++i) {
            printf("histo de %d = %d\n", i, histo[i]);
        }
    }
}

void cliente3(){
    char t[] = "77555";
    int runLess[4];

    if(bipolar_number(t) == 0){
        for (int i = 0; i < 4; ++i) {
            runLess[i] = 0;
        }
        //RL_V1(t, runLess);
        RL_V2(t, runLess);
        printf("RL\n");
        for (int i = 0; i < 4; ++i) {
            printf("%d ", runLess[i]);
        }
    }
}

int bipolar_number(char *text){

    int bipolar = 0, changes = 0, exits = 0;
    int number, pow, digits = 0;
    char *str = &text[0];

    for (int i = 0; i < strlen(text); ++i) {
        if(isalpha(text[i])){
            printf("Nao pode ter letras\n");
            return -1;
        }
        if(text[i] != text[i+1]){
            changes++;
        }
    }
    changes--;
    if(changes == 1){
        for (int i = 0; i < 3; ++i) {
            *(str+i) = text[i];
            if(text[i] == text[i+1]){
                bipolar = 1;
            }
        }
        number = atoi(str);
        return 0;
    }
    else{
        return -1;
    }
}

void print_bipolar_numbers(int k){

    int n[4] = {};
    int num = 1, rightNum = 0, leftNum = 1;
    int j = 0, changePos = k-1;

    /*
    for (int i = 0; i < k; ++i) {
        n[i] = leftNum;
        printf("%d", n[i]);
    }
    */

    while (1){
        if(leftNum == 9 && changePos == 0 && rightNum == 8){
            break;
        }
        if(rightNum == 9 && changePos == 0){
            rightNum = 0;
            leftNum++;
        }
        if(changePos == 0){
            changePos = k-1;
            if(rightNum != 9){
                rightNum++;
            } else{
                rightNum = 0;
            }
        }
        if(leftNum == rightNum){
            rightNum++;
        }
        if(j >= changePos){
            n[j] = rightNum;
        } else{
            n[j] = leftNum;
        }
        if(j == k){
            printf("\t");
            changePos--;
            j = 0;
        } else{
            printf("%d", n[j]);
            j++;
        }
    }
}

int hist(char* num, int histo[]){
    for (int i = 0; i < 10; ++i) {
        histo[i] = 0;
    }
    for (int i = 0; i < strlen(num); ++i) {
        histo[*(num+i)-'0']++;
    }
    return 0;
}

int RL_V1(char* num, int runLess[]){
    int runLessPos = 0;
    char temp;
    for (int i = 0; i < strlen(num); ++i) {
        if(i == 0){
            runLess[runLessPos]++;
        } else{
            if(*(num+i) == temp){
                runLess[runLessPos]++;
            } else{
                runLessPos++;
                runLess[runLessPos] = temp-'0';
                runLessPos++;
                runLess[runLessPos]++;
            }
        }
        temp = *(num+i);
    }
    runLessPos++;
    runLess[runLessPos] = temp-'0';
}

int RL_V2(char* num, int runLess[]){
    int runLessPos = 0;
    runLess[runLessPos] = 1;
    runLess[runLessPos+1] = *(num)-'0';
    for (int i = 1; i < strlen(num); ++i) {
        if(*(num+i) != *(num+(i-1))){
            runLessPos += 2;
            runLess[runLessPos+1] = *(num+i)-'0';
        }
        runLess[runLessPos]++;
    }
}