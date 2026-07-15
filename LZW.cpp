#include "LZW.h"
#include <iostream>
using namespace std;
#include <string>

LZW::LZW(){
    
}

LZW::~LZW(){}

string LZW::comprime(string str){
    int codigo[1000];
    string dic[1000];
    int tamDic = 0;
    bool encontrado;

    for(int i = 0; i < str.length(); i++) {
        encontrado = false;
        
        for(int j = 0; j <= i; j++) {
            if (dic[j][0] == str[i]){
                encontrado = true;
                break;
            }
        }
        
        if(!encontrado){
            dic[tamDic] = string(1, str[i]);
            tamDic++;
        }
   }
   
    string prefixo = string(1, str[0]);
    int p;
    int cont = 0;

    for(int j = 0; j < str.length() - 1; j++) {
        char c = str[j + 1];
        bool encontrou = false;

        for (int i = 0; i < tamDic; i++){
            if (prefixo + string(1, c) == dic[i]) {
                prefixo += c;
                encontrou = true;
                break;
            }
        }

        if (!encontrou){
            int p = -1;
            for (int i = 0; i < tamDic; i++) {
                if(dic[i] == prefixo) {
                    p = i;
                    break;
                }
            }
        
            codigo[cont++] = p;
            dic[tamDic++] = prefixo + c;
            prefixo = string(1, c);
        }
    }

    string stringComprimida = "";
    for (int i = 0; i < cont; i++) {
        stringComprimida += "(" + to_string(codigo[i]) + ")";
        if(i < cont - 1)
            stringComprimida += ", ";
    }
    return stringComprimida;
}

string LZW::descomprime(string str){
    
}
