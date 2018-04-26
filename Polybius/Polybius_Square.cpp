#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
string once;

void encrypte_eng(char mass_eng[5][5], ifstream &fin, ofstream &fout){
	int shift;
	int count_i = 0, count_j = 0;
	fin >> shift;
	int mass_coor[2048], count_k = 0, count_x = 0;
	char symbol;
	while(1){
		symbol = fin.get();
		if(fin.eof()){
			break;
		}
		if(symbol != '\n'){
			for(count_i = 0; count_i < 5; count_i++){
				for(count_j = 0; count_j < 5; count_j++){
					if(symbol == (char)mass_eng[count_i][count_j]){
						break;
					}
				}
				if(symbol == (char)mass_eng[count_i][count_j]){
					break;
				}
			}
			count_x++;
			mass_coor[count_k] = count_i;
			count_k++;
			mass_coor[count_k] = count_j;
			count_k++;
		}
	}
	count_x = count_x*2;;
	count_i = shift;
	while(count_i != (count_x - 1)){
		fout << mass_eng[mass_coor[count_i]][mass_coor[count_i + 1]];
		count_i += 2;
	}
	fout << mass_eng[mass_coor[count_x - 1]][mass_coor[0]];
	count_i = 1;
	while(count_i != shift){
		fout << mass_eng[mass_coor[count_i]][mass_coor[count_i + 1]];
		count_i += 2;
	}
}

void decrypt_eng(char mass_eng[5][5], ifstream &fin, ofstream &fout){
	int count_i = 0, count_j = 0;
	int shift;
	fin >> shift;
	int mass_coor[2048], count_k = 0, count_x = 0;
	char symbol;
	while(1){
		symbol = fin.get();
		if(fin.eof()){
			break;
		}
		if(symbol != '\n'){
			for(count_i = 0; count_i < 5; count_i++){
				for(count_j = 0; count_j < 5; count_j++){
					if(symbol == mass_eng[count_i][count_j]){
						mass_coor[count_k] = count_i;
						count_k++;
						mass_coor[count_k] = count_j;
						count_k++;
						break;
					}
					if(symbol == mass_eng[count_i][count_j]){break;}
				}
			}
			count_x++;
		}
	}
	count_x = count_x*2;;
	count_i = shift;
	count_j = count_x - count_i;
	while(count_j < count_x - 2){
		fout << mass_eng[mass_coor[count_j]][mass_coor[count_j + 1]];
		count_j += 2;
	}
	fout <<mass_eng[mass_coor[count_x - 1]][mass_coor[0]];
	count_j = count_x - count_i;
	count_x = 1;
	while(count_x < count_j){
		fout << mass_eng[mass_coor[count_x]][mass_coor[count_x + 1]];
		count_x += 2;
	}

	
	
}

void encrypte_rus(char mass_rus[6][6], ifstream &fin, ofstream &fout){
	
	
}

void decrypt_rus(char mass_rus[6][6], ifstream &fin, ofstream &fout){
	
	
}

int main(int argc, char* argv[]){
	ifstream fin(argv[1]);
	ofstream fout("output.txt");
	char mass_eng[5][5], mass_rus[6][6];
	int count_i = 0, count_j = 0, count_k = 65; //count_k для работы с ascii
	for(count_i = 0; count_i < 5; count_i++){
		for(count_j = 0; count_j < 5; count_j++){
			if(count_k == 74){count_k++;}
			mass_eng[count_i][count_j] = char(count_k);
			count_k++;
		}
	}
	fin >> once;
	if(once == "encrypte"){
		fin >> once;
		if(once == "english"){
			encrypte_eng(mass_eng, fin, fout);
		}
		if(once == "russian"){
			encrypte_rus(mass_rus, fin, fout);
		}
	}
	if(once == "decrypt"){
		fin >> once;
		if(once == "english"){
			decrypt_eng(mass_eng, fin, fout);
		}
		if(once == "russian"){
			decrypt_rus(mass_rus, fin, fout);
		}
	}
	return 0;
}
