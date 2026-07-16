#include <dirent.h>
#include "manipulacaoArquivos.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

bool verBinario(const char *caminho) {
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

string lerArquivoCompressao(const char *caminho, int tamN){
    DIR *dir = opendir(caminho);

    if (dir == nullptr) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entrada;

    string linhasLidasConcatenadas;

    // fazer vetor ordenado com N numeros aleatorios
    int* numAleatorios = new int[tamN];

    random_device rd;  
    mt19937 gen(rd()); 

    uniform_int_distribution<> distrib(0, tamN-1); 

    for (int i = 0; i < tamN; i++){
        numAleatorios[i] = distrib(gen);
    }
    
    // peguei um Bubble Sort do material de algoritmos 2
    for(int i = 0; i < tamN-1; i++){
        for(int j = 0; j < tamN - 1 - i; j++){
            if(numAleatorios[j] > numAleatorios[j+1]){
                int aux = numAleatorios[j];
                numAleatorios[j] = numAleatorios[j+1];
                numAleatorios[j+1] = aux;
            }
        }
    }

    int contLinhas = 0;
    int contVetor = 0;

    while ((entrada = readdir(dir)) != nullptr) {
        string nomeArquivo = entrada->d_name;

        if (nomeArquivo.length() >= 4) {
            string extensao = nomeArquivo.substr(nomeArquivo.length() - 4);

            if (extensao != ".bin") {
                ifstream entrada;
                string linha;

                if (entrada.is_open()) {
                    while (getline(entrada, linha)) {
                        if (contLinhas == numAleatorios[contVetor]){
                            linhasLidasConcatenadas += linha;
                            contVetor++;
                        }
                        contLinhas++;
                    }
                    entrada.close();
                } else {
                    cout << "Não foi possível abrir o arquivo" << '\n';
                }
            }
        }

        cout << nomeArquivo << endl;
    }

    closedir(dir);

    return linhasLidasConcatenadas;

}