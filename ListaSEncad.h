#include "No.h"
#ifndef LISTASENCAD_H__
#define LISTASENCAD_H__


class ListaSEncad{
    private:
    No* inicio;
    int n;

    public: 
    ListaSEncad();
    ~ListaSEncad();
    void set(char info, int val);
    void setNo(No* p);
    No* removerPrimeiro();
    No* busca(int val);
    void imprime();
    int tamanho();
    No* getInicio();
    void merge(ListaSEncad &L2);
};


#endif