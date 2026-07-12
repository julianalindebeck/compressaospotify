#include "ListaSEncad.h"
#include <iostream>
using namespace std;

ListaSEncad::ListaSEncad(){
    inicio = nullptr;
    n = 0;
}

ListaSEncad::~ListaSEncad(){
    No* p = inicio;
    No* temp = p;
    while (p != nullptr){
        temp = p->getProx();
        delete p;
        p = temp;
    }
    inicio = nullptr;
}

void ListaSEncad:: set(char info, int val){
    No* novo = new No(info, val);
    if(n == 0){
        inicio = novo;
        n++;
        return;
    }
    else{
        No* temp = inicio;
        while (temp != nullptr && temp->getFrequencia() < val){
            temp = temp->getProx();
        }
        if (temp == inicio){
            novo->setProx(inicio);
            inicio = novo;
            n++;
            return;
        }
        else if (temp == nullptr){
            No* ant = inicio;
            while (ant->getProx() != temp){
                ant = ant->getProx();
            }
            ant->setProx(novo);
            n++;
            return;
        }
        else{
            No* ant = inicio;
            while (ant->getProx() != temp){
                ant = ant->getProx();
            }
            novo->setProx(temp);
            ant->setProx(novo);
            n++;
            return;
        }
    }
}

void ListaSEncad:: setNo(No* p){
    if(n == 0){
        inicio = p;
        n++;
        return;
    }
    else{
        No* temp = inicio;
        while (temp != nullptr && temp->getFrequencia() < p->getFrequencia()){
            temp = temp->getProx();
        }
        if (temp == inicio){
            p->setProx(inicio);
            inicio = p;
            n++;
            return;
        }
        else if (temp == nullptr){
            No* ant = inicio;
            while (ant->getProx() != temp){
                ant = ant->getProx();
            }
            ant->setProx(p);
            n++;
            return;
        }
        else{
            No* ant = inicio;
            while (ant->getProx() != temp){
                ant = ant->getProx();
            }
            p->setProx(temp);
            ant->setProx(p);
            n++;
            return;
        }
    }
}

int ListaSEncad:: tamanho(){
    return n;
}

No* ListaSEncad::removerPrimeiro() {
    if (inicio == nullptr)
        return nullptr;

    No* p = inicio;
    inicio = inicio->getProx();
    p->setProx(nullptr);
    n--;

    return p;
}

No* ListaSEncad:: busca(int val){
    No* temp = inicio;
    while (temp != nullptr){
        if (temp->getFrequencia() == val){
            return temp;
        }
        temp = temp->getProx();
    }
    return nullptr;
}

void ListaSEncad:: imprime(){
    No* temp = inicio;
    while (temp != nullptr){
        cout << temp->getFrequencia() << " ";
        temp = temp->getProx();
    }
    return;
}

No* ListaSEncad:: getInicio(){
    return inicio;
}

void ListaSEncad:: merge(ListaSEncad &L2){
    No* temp = L2.inicio;
    while (temp != nullptr){
        set(temp->getCaractere(), temp->getFrequencia());
        temp = temp->getProx();
    }
}