#include "LZW.h"
#include <iostream>
#include <string>
using namespace std;


LZW::LZW(){
    
}

LZW::~LZW(){}

string LZW::comprime(string str){
    bool encontrado;

    for(int i = 0; i < str.length(); i++) {
        encontrado = false;
        
        for(int j = 0; j < tamDic; j++) {
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

    int p = -1;
    for (int i = 0; i < tamDic; i++) {
        if(dic[i] == prefixo) {
            p = i;
            break;
        }
    }

    if (p != -1) {
        codigo[cont++] = p;
    }

    string stringComprimida = "";
    for (int i = 0; i < cont; i++) {
        stringComprimida += "(" + to_string(codigo[i]) + ")";
        if(i < cont - 1)
            stringComprimida += ",";
    }
    return stringComprimida;
}

string LZW::descomprime(string str){
    string descomprimida= "";
    for(int i=0; i<str.length(); i++){
        if(str[i] == '('){
            descomprimida+=dic[str[i+1]-'0'];
        }
    }
    return descomprimida;
}
