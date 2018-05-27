#include <stdio.h>
#include <fstream>
#include <iostream>
#include <inttypes.h>
#include <cstdio>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "string.h"


#define BUF_SIZE 1024
using namespace std;
uint64_t eval(char *str);
uint64_t number(char *, uint64_t *);
uint64_t expr(char *, uint64_t *);
uint64_t term(char *, uint64_t *);
uint64_t factor(char *, uint64_t *);

int main(int argc, char** argv)
{
    char str[BUF_SIZE];
    int j = 0;
    char strr[BUF_SIZE];
    char* input_file = 0;
    char* output_file = 0;
    for(int i = 0; i < argc; i++){
      if (strstr(argv[i], "-i") or strstr(argv[i], "input")){
        input_file = argv[i + 1];
      }
      if (strstr(argv[i], "-o") or strstr(argv[i], "output")){
        output_file = argv[i + 1];
      }
    }
    FILE * ptrFile = fopen(input_file , "r");
    if(fgets(str, BUF_SIZE, ptrFile));
    if(str[0] != 'F'){
      cerr << "Error no formula f in the file" << endl;
      exit(1);
    }
    if(str[1] != '='){
      cerr << "invalid input. Maybe need F='formula'" << endl;
      exit(1);
    }
    for(uint64_t i = 2; i < strlen(str); i++){
        if(str[i] != ' '){
          strr[j] = str[i];
          j++;
        }
    }
    fclose(ptrFile);
    char* ptr = strr;
    int count_br_one = 0, count_br_two = 0;
    ofstream fout;
    fout.open(output_file);
    /*if((ptr = strstr(ptr, "+")) == NULL){
        fout << eval(strr);   
        fout.close();
        exit(1);
    }
    if((ptr = strstr(ptr, "*")) == NULL){
        fout << eval(strr);   
        fout.close();
        exit(1);
    }*/
    while((ptr = strstr(ptr, "(")) != NULL){
      ptr += 1;
      count_br_one += 1;
    }
    ptr = strr;
    while((ptr = strstr(ptr, ")")) != NULL){
      ptr += 1;
      count_br_two += 1;
    }
    if(count_br_one != count_br_two){
      cerr << "Unbalanced bracket" << endl;
      exit(1);
    }
    for(uint64_t i = 0; i < (strlen(strr) - 1); i++){
      if(strr[i] == '(' && strr[i+1] == ')'){
        cerr << "no expression found at pos " << i+2 <<  endl;
        exit(1);
      }
    }
    fout << eval(strr); 
    printf("%" PRIu64 "\n", eval(strr));  
    fout.close();
    return 0;
}

uint64_t eval(char *str)
{
    uint64_t i = 0;
    return expr(str, &i);
}

uint64_t number(char *str, uint64_t *idx)
{
    uint64_t result = 0;
    uint64_t div = 10;
    int sign = 1;
    if (str[*idx] == '-'){
        sign = -1;
        ++*idx;
    }
    while (str[*idx] >= '0' && str[*idx] <= '9'){
        result = result * 10 + (str[*idx] - '0');
        ++*idx;
    }
    if (str[*idx] == '.'){
        ++*idx;
        while (str[*idx] >= '0' && str[*idx] <= '9'){
            result = result + (str[*idx] - '0') / div;
            div *= 10;
            ++*idx;
        }
    }
    return sign * result;
}

uint64_t expr(char *str, uint64_t *idx){
    uint64_t result = term(str, idx);
    while (str[*idx] == '+' || str[*idx] == '-'){
        switch (str[*idx]){
        case '+':
            ++*idx;
            result += term(str, idx);
            break;
        }
    }
    return result;
}

uint64_t term(char *str, uint64_t *idx){
    uint64_t result = factor(str, idx);
    while (str[*idx] == '*'){
        switch (str[*idx]){
        case '*':
            ++*idx;
            result *= factor(str, idx);
            break;
        }
    }
    return result;
}

uint64_t factor(char *str, uint64_t *idx){
    uint64_t result;
    int sign = 1;
    if (str[*idx] == '('){
        ++*idx;
        result = expr(str, idx);
        if (str[*idx] != ')'){
            printf("Brackets unbalanced!\n");
            exit(-2);
        }
        ++*idx;
    }
    else
        result = number(str, idx);
    return sign * result;
}
