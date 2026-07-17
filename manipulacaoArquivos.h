#ifndef MANIPULACAOARQUIVOS_H
#define MANIPULACAOARQUIVOS_H

#include "Huffman.h"
#include "LZ77.h"
#include "LZW.h"
#include <string>
using namespace std;

class manipulacaoArquivos {
    private:
        const char* arquivos;
        int n;
        float taxa = 0;

    public:
        manipulacaoArquivos(const char* caminho, int tamN);
        ~manipulacaoArquivos();
        int contarLinhas(const string& caminhoCompleto);
        bool verBinario(const char *caminho);
        bool lerLinhaCSV(istream& input, string& linhaCompleta);
        string lerArquivoCompressao(const char *caminho, int tamN);
        string comprime(string str, int metodo);
        string descomprime(string str, int metodo);
        void escreveBinario(string comprimida);
        void comprime(int metodo);
        void descomprime(int metodo);
        float getTaxa();
        void escreveTaxaTXT(float taxas[], int metodos[], int vezes);

};

#endif