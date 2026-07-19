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
    
    string lista = "[";
    for (int i = 0; i < tam; i++){
        lista += "(";
        lista += simbolos[i].caractere; 
        lista += ",";
        lista += to_string(simbolos[i].frequencia); 
        lista += ")";
        novaLista->set(simbolos[i].caractere, simbolos[i].frequencia);
    }
    lista += "]\n";

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

    raiz = novaLista->removerPrimeiro();
    delete novaLista; 

    string cod = "";
    gerarCodigo(raiz, cod, simbolos, tam);

    string resultado = compressao(str, simbolos, tam, lista);
    delete[] simbolos; 
    return resultado;
}

string Huffman:: compressao(string str, Simbolo simbolos[], int tam, string lista){
    string comprimido = "";
    for (char c: str){
        for (int i = 0; i < tam; i++){
            if (simbolos[i].caractere == c){
                comprimido += simbolos[i].codigo;
                break;
            }
        }
    }

    lista += comprimido;

    return lista;
   
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

string Huffman:: descompressao (string str){
    ListaSEncad* novaLista = new ListaSEncad();

    int i = 0;
    if (str.length() > 0 && str[i] == '[') i++; 

    while (i < str.length()) {
        if (str[i] == ']' && i + 1 < str.length() && str[i+1] == '\n') {
            i += 2;
            break;
        }

        if (str[i] == '(') {
            i++; 
            if (i >= str.length()) break; 
            char c = str[i]; 
            i++; 
            
            if (i < str.length() && str[i] == ',') {
                i++;
                string frequencia = "";
                while (i < str.length() && str[i] != ')') {
                    frequencia += str[i];
                    i++;
                }
                
                if (!frequencia.empty()) {
                    novaLista->set(c, stoi(frequencia));
                }
            }
        } else {
            i++; 
        }
    }

    if (novaLista->tamanho() == 0) {
        delete novaLista;
        return ""; 
    }

    while (novaLista->tamanho() > 1){
        No* menor = novaLista->getInicio();
        No* segundoMenor = menor->getProx();

        if (!menor || !segundoMenor) break; 

        int somaFreq = menor->getFrequencia() + segundoMenor->getFrequencia();

        No* novo = new No('\0', somaFreq);

        novaLista->removerPrimeiro();
        novaLista->removerPrimeiro();

        novo->setEsq(menor);
        novo->setDir(segundoMenor);

        novaLista->setNo(novo);
    }

    raiz = novaLista->removerPrimeiro();
    delete novaLista; 
    
    if (raiz == nullptr) {
        return "";
    }

    string subString = "";
    if (i < str.length()) {
        subString = str.substr(i); 
    }

    string descomprimida = "";
    No* temp = raiz;
    
    for (char c: subString){
        if (temp == nullptr) break; 

        if (c == '0'){
            temp = temp->getEsq();
        }
        else if(c == '1'){
            temp = temp->getDir();
        } 
        else {
            continue; 
        }

        if (temp != nullptr && temp->getEsq() == nullptr && temp->getDir() == nullptr){
            descomprimida += temp->getCaractere();
            temp = raiz; 
        }
    }
    
    return descomprimida;
}