#ifndef MANIPULACAOARQUIVOS_H
#define MANIPULACAOARQUIVOS_H

#include <string>
using namespace std;

bool verBinario(const char *caminho);

string lerArquivoCompressao(const char *caminho, int tamN);

// falta a descompressao: (o algoritmo que eu pensei: ler o arquivo binário, transformar pra texto, pegar o método inscrito, descomprimir conforme o método, escrever a descompressão no arquivo .txt e salvar)

#endif