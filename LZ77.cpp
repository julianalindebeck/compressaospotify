#include "LZ77.h"
#include <iostream>
using namespace std;
#include <string>

LZ77::LZ77(){
    nd = 6;
    nb = 4;
}

LZ77::~LZ77(){}

string LZ77::comprime(string str){
    CodigoLZ77* codigo = new CodigoLZ77[str.length()];
    int cursor = 0;
    int dic;
    int maiorSeq;
    int maiorPos;
    int cont = 0;
    while (cursor < str.length())
    {
       dic = max(0,cursor-nd);
       maiorSeq = 0;
       maiorPos = 0;
       
       for(int i=dic; i<cursor; i++){
            int tam = 0;

            while(tam < nb && cursor+tam < str.length() && str[i+tam] == str[cursor+tam]){
                tam++;
            }

            if(tam > maiorSeq){
                maiorSeq = tam;
                maiorPos = cursor - i;
            }
       }
       char posSeq = (cursor+maiorSeq) > str.length() ? '\0' : str[cursor + maiorSeq];

       codigo[cont].pos = maiorPos;
       codigo[cont].seq = maiorSeq;
       codigo[cont].posSeq = posSeq;
       cursor += maiorSeq+1;
       cont++;
    }

    string compressao;
    for(int i=0; i<cont; i++){
        compressao += "(" + to_string(codigo[i].pos) + "," + to_string(codigo[i].seq) + "," + ((codigo[i].posSeq == '\0') ? "null" : string(1, codigo[i].posSeq)) + ")";

        if(i != cont-1){
            compressao += ",";
        }
    }
    return compressao;
}

string LZ77::descomprime(string str){
    CodigoLZ77* codigo = new CodigoLZ77[str.length()];
    int cont = 0;
    
    int i = 0;
    while (i < str.length()) {
        if (str[i] == '(') {
            i++;
            
            string s_pos = "";
            while (i < str.length() && str[i] != ',') {
                s_pos += str[i];
                i++;
            }
            i++;
            
            string s_seq = "";
            while (i < str.length() && str[i] != ',') {
                s_seq += str[i];
                i++;
            }
            i++; 
            
            string s_char = "";
            while (i < str.length() && str[i] != ')') {
                s_char += str[i];
                i++;
            }
            
            if (!s_pos.empty() && !s_seq.empty()) {
                codigo[cont].pos = stoi(s_pos);
                codigo[cont].seq = stoi(s_seq);
                
                if (s_char == "null") {
                    codigo[cont].posSeq = '\0';
                } else if (!s_char.empty()) {
                    codigo[cont].posSeq = s_char[0];
                } else {
                    codigo[cont].posSeq = '\0';
                }
                cont++;
            }
        }
        i++;
    }

    string descomprimida = "";
    for(int i = 0; i < cont; i++){
        if(codigo[i].pos == 0 && codigo[i].seq == 0){
            descomprimida += codigo[i].posSeq;
        }
        else{
            if (codigo[i].pos <= descomprimida.length()) {
                int inicioSubstr = descomprimida.length() - codigo[i].pos;
                
                if(codigo[i].pos < codigo[i].seq){
                    string temp = "";
                    for(int j = 0; j < nb; j++){
                        temp += descomprimida.substr(inicioSubstr, codigo[i].pos);
                    }
                    descomprimida += temp.substr(0, codigo[i].seq);
                }
                else{
                    descomprimida += descomprimida.substr(inicioSubstr, codigo[i].seq);
                }
            }
            
            if(codigo[i].posSeq != '\0') {
                descomprimida += codigo[i].posSeq;
            }
        }
    }

    delete[] codigo;
    return descomprimida;
}