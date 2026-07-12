#include "No.h"
#include <iostream>
using namespace std;

No::No(char info, int val){
    esquerda = nullptr;
    direita = nullptr;
    proximo = nullptr;
    
    frequencia = val;
    caractere = info;
}

No:: ~No(){}

void No::setFrequencia(int val){
    frequencia = val;
}

void No::setCaractere(char info){
    caractere = info;
}

void No::setEsq(No* novo){
    esquerda = novo;
}

void No::setDir(No* novo){
    direita = novo;
}

void No::setProx(No* novo){
    proximo = novo;
}

No* No::getEsq(){
    return esquerda;
}

No* No::getDir(){
    return direita;
}

No* No::getProx(){
    return proximo;
}

int No::getFrequencia(){
    return frequencia;
}

char No::getCaractere(){
    return caractere;
}