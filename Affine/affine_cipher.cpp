#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
char buff[2048]; //Для хранения прочитанного из файла
string once;


int evklid(int a){
  int b = 26;
  while (b)
       b ^= a ^= b ^= a %= b;
   if(a != 1){
    cout << "ERROR a & b are not mutually prime" << endl;
    exit(0);
   }
   return 0;
}

int gcd(int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return x;
}


int main(int argc, char* argv[]){
	int a = 1, b = 0, x = 26, N = 26, y =26, i=0 , j=0, ifbreak = 0, m = 0;
  char symbol;
	ifstream fin(argv[1]);
  ofstream fout("output.txt");
  fin >> once;
  if(once == "break"){
    ifbreak  = 1;
    char shif[2], deshif[2];
    int letter1 = 0, letter2 = 0, letter3 = 0, letter4 = 0;
    fin >> shif;
    fin >> deshif;
    letter1 = (int)shif[0] - 65;
    letter2 = (int)shif[1] - 65;
    letter3 = (int)deshif[0] - 65;
    letter4 = (int)deshif[1] - 65;
    a = (letter4 - letter2)/(letter3 - letter1);
    b = letter3 - letter1*a;
    b = b%26;
    a = gcd(a , N , x , y);
    a = 26 - a;
    //cout << a << " " << b << endl;
    while(1){
      symbol = fin.get();
      if(fin.eof()){
        break;
      }
      if(symbol != '\n'){
        if((int)symbol > 64 && (int)symbol < 91){
          m = (int)symbol - 65;
          m = (a*(m - b + 26))%26;
          m = m + 65;
          symbol = char(m);
        }
          fout << symbol;
      }
    }
  }
  if(ifbreak == 0){
    fin >> buff;
    a = atoi(buff);
    fin >> buff;
    b = atoi(buff);
    evklid(a);
  }
  if(once == "encrypte")
  {
    int c;
     while(1){
      symbol = fin.get();
       if(fin.eof()){
         break;
       }
         if((int)symbol > 64 && (int)symbol < 91){
           c = (int)symbol - 65;
           c = (c*a + b)%26;
           c = c + 65;
           symbol = char(c);
         }
           fout << symbol;
     }
  }
  if(once == "decrypt")
  {
    char symbol;
    if(ifbreak  == 1){
      a = i;
      b = j;
    }
    int c;
    a = gcd(a,N,x,y);
    if(a < 0){ 
      a = 26 + a;
    }
     while(1){
      symbol = fin.get();
       if(fin.eof()){
         break;
       }
         if((int)symbol > 64 && (int)symbol < 91){
           c = (int)symbol - 65;
           c = (a*(c - b + 26))%26;
           c = c + 65;
           symbol = char(c);
         }
           fout << symbol;
     }
  }
  fout.close();
  fin.close();
	return 0;
}
