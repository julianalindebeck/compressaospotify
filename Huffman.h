#ifndef HUFFMAN_H__
#define HUFFMAN_H__
#include "No.h"
#include "Simbolo.h"
#include <string>
using namespace std;

class Huffman{
    private:
    No* raiz;
    
    public:
    Huffman();
    ~Huffman();
    void destruir(No* inicio);
    string constroi(string str);
    string compressao(string str, Simbolo simbolos[], int tam);
    void gerarCodigo(No* q, string cod, Simbolo simbolos[], int tam);
    int montaTabela(string str, Simbolo* simbolos, int tam);
};



#endif