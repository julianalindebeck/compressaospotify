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
        compressao += "(" + to_string(codigo[i].pos) + ", " + to_string(codigo[i].seq) + ", " + ((codigo[i].posSeq == '\0') ? "null" : string(1, codigo[i].posSeq)) + ")";

        if(i != cont-1){
            compressao += ", ";
        }
    }
    return compressao;
}

string LZ77::descomprime(string str){

}
