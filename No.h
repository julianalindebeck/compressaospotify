#ifndef NO_H_
#define NO_H_

class No{
    private:
    No* esquerda;
    No* direita;
    No* proximo; // para a gente percorrer os nós criados
    char caractere;
    int frequencia;

    public:
    No(char info, int val);
    ~No();
    void setFrequencia(int val);
    void setCaractere(char info);
    void setEsq(No* novo);
    void setDir(No* novo);
    void setProx(No* novo);
    No* getEsq();
    No* getDir();
    No* getProx();
    int getFrequencia();
    char getCaractere();

};

#endif