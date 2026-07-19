#include "LZW.h"
#include <iostream>
#include <string>
using namespace std;


LZW::LZW(){
    dic = new string[capacidadeDic];
    codigo = new int[capacidadeCod];
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
            if (tamDic == capacidadeDic){
                aumentaDic();
            }
        }
   }
   
    string prefixo = string(1, str[0]);

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
        
            codigo[tamCod++] = p;
            if (tamCod == capacidadeCod){
                aumentaCod();
            }
            dic[tamDic++] = prefixo + c;
            if (tamDic == capacidadeDic){
                aumentaDic();
            }
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
        codigo[tamCod++] = p;
        if (tamCod == capacidadeCod){
            aumentaCod();
        }
    }

    string stringComprimida = "[";
    for (int i = 0; i < tamDic; i++){
        stringComprimida += "(" + dic[i] + ")";
        if(i < tamDic - 1)
            stringComprimida += ",";
    }
    stringComprimida += "]\n";

    for (int i = 0; i < tamCod; i++) {
        stringComprimida += "(" + to_string(codigo[i]) + ")";
        if(i < tamCod - 1)
            stringComprimida += ",";
    }
    return stringComprimida;
}

string LZW::descomprime(string str){
    int i = 0;
    
    if (str.length() > 0 && str[i] == '[') i++; 
    
    while (i < str.length()) {
        if (str[i] == ']' && i + 1 < str.length() && str[i+1] == '\n') {
            i += 2;
            break;
        }

        if (str[i] == '(') {
            i++;
            string prefixo = "";
            
            int j = i;
            while (j < str.length()) {
                if (str[j] == ')') {
                    if ((j + 1 < str.length() && str[j+1] == ',' && j + 2 < str.length() && str[j+2] == '(') ||
                        (j + 1 < str.length() && str[j+1] == ']' && j + 2 < str.length() && str[j+2] == '\n')) {
                        break; 
                    }
                }
                prefixo += str[j];
                j++;
            }
            i = j;
            
            dic[tamDic++] = prefixo;
            if (tamDic == capacidadeDic) aumentaDic();
            
        } else {
            i++; 
        }
    }

    string descomprimida = "";
    while (i < str.length()) {
        if (str[i] == '(') {
            i++;
            string numStr = "";
            while (i < str.length() && str[i] != ')') {
                numStr += str[i];
                i++;
            }
            if (!numStr.empty()) {
                int cod = stoi(numStr); 
                descomprimida += dic[cod];
            }
        }
        i++;
    }
    
    return descomprimida;
}

void LZW::aumentaDic(){
    capacidadeDic *= 2;
    string* novoDic = new string[capacidadeDic];

    for (int i = 0; i < tamDic; i++){
        novoDic[i] = dic[i];
    }

    delete [] dic;

    dic = novoDic;
}

void LZW::aumentaCod(){
    capacidadeCod *= 2;
    int* novoCod = new int[capacidadeCod];

    for (int i = 0; i < tamCod; i++){
        novoCod[i] = codigo[i];
    }

    delete [] codigo;

    codigo = novoCod;
}