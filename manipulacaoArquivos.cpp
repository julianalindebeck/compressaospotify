#include <dirent.h>
#include "manipulacaoArquivos.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>

using namespace std;

manipulacaoArquivos::manipulacaoArquivos(const char* caminho, int tamN){
    arquivos = caminho;
    n = tamN;
}

manipulacaoArquivos::~manipulacaoArquivos(){}

int manipulacaoArquivos::contarLinhas(const string& caminhoCompleto) {
    ifstream arquivo(caminhoCompleto);
    if (!arquivo.is_open()) return 0;
    
    string linha;
    int total = 0;
    while (lerLinhaCSV(arquivo, linha)) {
        total++;
    }
    return total;
}

bool manipulacaoArquivos::verBinario(const char *caminho) {
    DIR *dir = opendir(caminho);
    bool temBin = false;

    if (dir == nullptr) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entrada;

    while ((entrada = readdir(dir)) != nullptr) {
        string nomeArquivo = entrada->d_name;

        if (nomeArquivo.length() >= 4) {
            string extensao = nomeArquivo.substr(nomeArquivo.length() - 4);

            if (extensao == ".bin") {
                temBin = true;
            }
        }
        cout << nomeArquivo << endl;
    }

    closedir(dir);
    return temBin;
}

bool manipulacaoArquivos::lerLinhaCSV(istream& input, string& linhaCompleta) {
    linhaCompleta.clear();
    char ch;
    bool emAspas = false;

    while (input.get(ch)) {
        linhaCompleta += ch;

        if (ch == '"') {
            emAspas = !emAspas; 
        }

        if (ch == '\n' && !emAspas) {
            return true;
        }
    }

    return !linhaCompleta.empty();
}

string manipulacaoArquivos::lerArquivoCompressao(const char *caminho, int tamN){
    DIR *dir = opendir(caminho);

    if (dir == nullptr) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entrada;
    string linhasLidasConcatenadas;

    // Configuração do gerador de números aleatórios
    random_device rd;  
    mt19937 gen(rd()); 

    while ((entrada = readdir(dir)) != nullptr) {
        string nomeArquivo = entrada->d_name;

        if (nomeArquivo.length() >= 4) {
            string extensao = nomeArquivo.substr(nomeArquivo.length() - 4);

            if (extensao == ".csv") {
                string caminhoCompleto = string(caminho) + "/" + nomeArquivo;

                linhasLidasConcatenadas += nomeArquivo + ": ";

                int totalLinhas = contarLinhas(caminhoCompleto);
                if (totalLinhas == 0) continue; 

                int* numAleatorios = new int[tamN];
                uniform_int_distribution<> distrib(0, totalLinhas - 1); 

                for (int i = 0; i < tamN; i++){
                    numAleatorios[i] = distrib(gen);
                }
                
                for(int i = 0; i < tamN-1; i++){
                    for(int j = 0; j < tamN - 1 - i; j++){
                        if(numAleatorios[j] > numAleatorios[j+1]){
                            int aux = numAleatorios[j];
                            numAleatorios[j] = numAleatorios[j+1];
                            numAleatorios[j+1] = aux;
                        }
                    }
                }

                ifstream arquivoLeitura(caminhoCompleto);

                if (!arquivoLeitura.is_open()) {
                    cerr << "Não foi possível abrir o arquivo: " << caminhoCompleto << endl;
                    delete[] numAleatorios; 
                    continue; 
                }

                string linha;
                int contLinhas = 0;
                int contVetor = 0;

                while (lerLinhaCSV(arquivoLeitura, linha)) { 
                    
                    if (contVetor < tamN && contLinhas == numAleatorios[contVetor]) {
                        stringstream lineStream(linha);
                        bool emAspas = false;
                        string celulaAtual = "";
                        char ch;

                        while (lineStream.get(ch)) {
                            if (ch == '"') {
                                emAspas = !emAspas;
                                continue;
                            }
                            
                            if (ch == ',' && !emAspas) {
                                linhasLidasConcatenadas += celulaAtual + " | "; 
                                celulaAtual.clear();
                            } 
                            else {
                                celulaAtual += ch;
                            }
                        }
                        if (!celulaAtual.empty()) {
                            linhasLidasConcatenadas += celulaAtual + " ";
                        }

                        contVetor++;
                    }
                    contLinhas++;
                }

                arquivoLeitura.close();
                delete[] numAleatorios; 
            }
        }
    }

    closedir(dir);
    return linhasLidasConcatenadas;
}

string manipulacaoArquivos::comprime(string str, int metodo){
    if (metodo == 0){
        Huffman novaCompressao;
        return novaCompressao.constroi(str);
    }
    else if (metodo == 1){
        LZ77 novaCompressao;
        return novaCompressao.comprime(str);
    }
    else{
        LZW novaCompressao;
        return novaCompressao.comprime(str);
    }
}

string manipulacaoArquivos::descomprime(string str, int metodo){
    if (metodo == 0){
        Huffman novaDescompressao;
        return novaDescompressao.descompressao(novaDescompressao.constroi(str));
    }
    else if (metodo == 1){
        LZ77 novaDescompressao;
        return novaDescompressao.descomprime(str);
    }
    else{
        LZW novaDescompressao;
        return novaDescompressao.descomprime(novaDescompressao.comprime(str)); 
    }
}

void manipulacaoArquivos::comprime(int metodo){
    // esse método que vai fazer tudo: pega o método, ai le os arquivos, pegando a string.
    string arquivosRecuperados = lerArquivoCompressao(arquivos, n);
    cout << "Recuperado dos arquivos: " << arquivosRecuperados << endl;
    // Usa o método para comprimir a string
    string comprimida = comprime(arquivosRecuperados, metodo);

    cout << "Comprimida: " << comprimida;
    // dependendo do método, escrevemos as infos no arquivo antes sobre o método
    // escrevemos o arquivo binário com a compressao da string concatenada
    // salva o arquivo .bin no diretório

    // tem que fazer a taxa de compressao tambem
}

void manipulacaoArquivos::descomprime(int metodo){
    // esse método que vai fazer tudo
}