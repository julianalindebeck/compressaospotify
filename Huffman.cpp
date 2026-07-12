#include "Huffman.h"
#include "ListaSEncad.h"
#include <iostream>
#include <string>
using namespace std;

Huffman:: Huffman(){
    raiz = nullptr;
}

Huffman:: ~Huffman(){
    destruir(raiz);
}

void Huffman:: destruir(No* inicio){
    if (inicio == nullptr){
        return;
    }
    destruir(inicio->getEsq());
    destruir(inicio->getDir());

    delete inicio;
}

int Huffman:: montaTabela(string str, Simbolo* simbolos, int tam){
    bool achou;
    for(char c: str){
        achou = false;
        for (int i = 0; i < tam; i++){
            if (simbolos[i].caractere == c){
                simbolos[i].frequencia++;
                achou = true;
                break;
            }
        }
        if (!achou){
            simbolos[tam].caractere = c;
            simbolos[tam].frequencia = 1;
            tam++;
        }
    }

    return tam;
}

string Huffman:: constroi(string str){
    ListaSEncad* novaLista = new ListaSEncad();
    Simbolo* simbolos = new Simbolo[256];
    int tam = montaTabela(str, simbolos, 0);
    for (int i = 0; i < tam; i++){
        novaLista->set(simbolos[i].caractere, simbolos[i].frequencia);
    }

    while (novaLista->tamanho() > 1){
        No* menor = novaLista->getInicio();
        No* segundoMenor = menor->getProx();

        int somaFreq = menor->getFrequencia() + segundoMenor->getFrequencia();

        No* novo = new No('\0', somaFreq);

        novaLista->removerPrimeiro();
        novaLista->removerPrimeiro();

        novo->setEsq(menor);
        novo->setDir(segundoMenor);

        novaLista->setNo(novo);

    }

    raiz = novaLista->getInicio();

    string cod = "";

    gerarCodigo(raiz, cod, simbolos, tam);

    return compressao(str, simbolos, tam);

}

string Huffman:: compressao(string str, Simbolo simbolos[], int tam){
    string comprimido = "";
    for (char c: str){
        for (int i = 0; i < tam; i++){
            if (simbolos[i].caractere == c){
                comprimido += simbolos[i].codigo;
                break;
            }
        }
    }

    return comprimido;
   
}

void Huffman:: gerarCodigo(No* q, string cod, Simbolo simbolos[], int tam){
    if (q == nullptr){
        return;
    }
    if (q->getCaractere() != '\0'){
        for (int i = 0; i < tam; i++){
            if(q->getCaractere() == simbolos[i].caractere){
                simbolos[i].codigo = cod;
                break;
            }
        }
    }
    else{
        gerarCodigo(q->getEsq(), cod + "0", simbolos, tam);
        gerarCodigo(q->getDir(), cod + "1", simbolos, tam);
    }
}
