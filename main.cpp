#include <iostream>
#include <string>
#include "Huffman.h"
#include "LZ77.h"
using namespace std;

string comprime(string str, int metodo){
    if (metodo == 0){
        Huffman* novaCompressao = new Huffman();
        return novaCompressao->constroi(str);
    }
    if (metodo == 1){
        LZ77* novaCompressao = new LZ77();
        return novaCompressao->comprime(str);
    }
    return "";
}

string descomprime(string str, int metodo){
    if (metodo == 1){
        LZ77* novaDescompressao = new LZ77();
        return novaDescompressao->descomprime(str);
    }
    return "";
}

int main(){

    // recuperar N registros dos arquivos e menu bla bla

    cout << endl << "O que gostaria de testar Professora Bárbara Quintela?" << endl;
    cout << "1. Comprimir uma string passada como parâmetro " << endl;
    cout << "2. Descomprimir uma string passada como parâmetro " << endl;
    cout << "Escolha a opção: ";
    
    int opcao;
    int metodo;
    cin >> opcao;

    if (opcao == 1){
        string str;
        cout << "Digite a string: ";
        cin >> str;

        cout << endl << "Agora escolha o método! " << endl;
        cout << "0. Huffman" << endl;
        cout << "1. LZ77" << endl;
        cout << "Escolha a opção: ";

        cin >> metodo;

        string stringComprimida = comprime(str, metodo);

        float taxaCompressao;

        cout << "String comprimida: " << stringComprimida << endl;
        int tamanhoCompressao;
        if (stringComprimida.length() % 8 == 0){
            tamanhoCompressao = stringComprimida.length()/8;
        }
        else{
            tamanhoCompressao = (stringComprimida.length()/8) + 1;
        }
        taxaCompressao = (float)(str.length() - tamanhoCompressao)/ str.length();
        cout << "Taxa de Compressão: " << taxaCompressao*100 << "%" << endl;
    }
    else if(opcao == 2){
        string str;
        cout << "Digite a string: ";
        cin >> str;

        cout << endl << "Agora escolha o método! " << endl;
        cout << "0. Huffman" << endl;
        cout << "1. LZ77" << endl;
        cout << "Escolha a opção: ";

        cin >> metodo;

        string stringDescomprimida = descomprime(str, metodo);

        cout << "String descomprimida: " << stringDescomprimida << endl;
    }
    return 0;
}