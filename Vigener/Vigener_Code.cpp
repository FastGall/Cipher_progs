#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;
string once;

void encrypt(ifstream &fin, ofstream &fout){
    int len_key, len_word, count_i = 0, count_j = 0, symb_k;
    char key[100], symbol;
    fin >> len_key;
    fin >> key;
    fin >> len_word;
    symbol = fin.get();
    while(count_j != len_word){
        symbol = fin.get();
        if(symbol > 64 && symbol < 91){
            symb_k = (int)symbol - 130 + (int)key[count_i];
            symb_k = symb_k%26 + 65;
            symbol = (char)symb_k;
            count_i++;
            if(count_i == len_key){count_i = 0;}
        }
        fout << symbol;
        count_j++;
    }
}

void decrypt(ifstream &fin, ofstream &fout)
{
    int len_key, len_word, count_i = 0, count_j = 0, symb_k;
    char key[100], symbol;
    fin >> len_key;
    fin >> key;
    fin >> len_word;
    symbol = fin.get();
    while (count_j != len_word)
    {
        symbol = fin.get();
        if (symbol > 64 && symbol < 91)
        {
            symb_k = (int)symbol - (int)key[count_i];
            if(symb_k < 0){symb_k = 26 + symb_k;}
            symb_k += 65;
            symbol = (char)symb_k;
            count_i++;
            if (count_i == len_key)
            {
                count_i = 0;
            }
        }
        if (symbol > 96 && symbol < 91)
        {
            symb_k = (int)symbol - (int)key[count_i];
            if (symb_k < 0)
            {
                symb_k = 26 + symb_k;
            }
            symb_k += 65;
            symbol = (char)symb_k;
            count_i++;
            if (count_i == len_key)
            {
                count_i = 0;
            }
        }
        fout << symbol;
        count_j++;
    }
}

int main(int argc, char *argv[])
{
    ifstream fin(argv[1]);
    ofstream fout("output.txt");
    fin >> once;
    if(once == "encrypt"){
        encrypt(fin, fout);
    }
    if(once == "decrypt"){
        decrypt(fin, fout);
    }
    cout << "attack at down"<< endl;
    return 0;
}