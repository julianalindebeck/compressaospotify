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

    public:
        manipulacaoArquivos(const char* caminho, int tamN);
        ~manipulacaoArquivos();
        int contarLinhas(const string& caminhoCompleto);
        bool verBinario(const char *caminho);
        bool lerLinhaCSV(istream& input, string& linhaCompleta);
        string lerArquivoCompressao(const char *caminho, int tamN);
        // falta a descompressao: (o algoritmo que eu pensei: ler o arquivo binário, transformar pra texto, pegar o método inscrito, descomprimir conforme o método, escrever a descompressão no arquivo .txt e salvar)
        string comprime(string str, int metodo);
        string descomprime(string str, int metodo);
        void comprime(int metodo);
        void descomprime(int metodo);

};

#endif