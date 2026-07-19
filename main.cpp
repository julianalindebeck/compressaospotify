#include <iostream>
#include <fstream>
#include <string>
#include "manipulacaoArquivos.h"
using namespace std;

int main(int argc, char *argv[]){

    int tamN = stoi(argv[2]);

    float taxasCompressao[1000];
    int metodosTaxas[1000];
    int vezesCompressao = 0;

    // ainda tem que fazer as estatísticas de desempenho

    cout << endl << "Lendo " << tamN << " registros aletórios dos arquivos..." << endl;

    while (true){

        manipulacaoArquivos gerenciador(argv[1], tamN);

        // procurando os arquivos
        if(gerenciador.verBinario(argv[1])){
            // salvar os arquivos binários

            cout << endl << "=============== MENU ===============" << endl;
            cout << endl << "ESCOLHA A OPÇÃO: " << endl;
            cout << "1. Descomprimir arquivo binário " << endl;
            cout << "2. Comprimir arquivos texto " << endl;
            cout << "3. Analisar taxas de compressão " << endl;
            cout << "4. Sair" << endl;
            cout << "Escolha a opção: ";
            int opcao;
            cin >> opcao;
            
            if (opcao == 1){
                // descomprime os arquivos e salva no diretorio 
                gerenciador.tipoDescompressao();
            }
            else if (opcao == 2){
                cout << endl << "ESCOLHA O MÉTODO DE COMPRESSÃO PARA OS REGISTROS" << endl;
                cout << "0. Huffman" << endl;
                cout << "1. LZ77" << endl;
                cout << "2. LZW" << endl;
                cout << "Escolha a opção: ";
                int metodo;
                cin >> metodo;
                cout << endl << "Comprimindo..." << endl;

                gerenciador.comprime(metodo);
                taxasCompressao[vezesCompressao] = gerenciador.getTaxa();
                metodosTaxas[vezesCompressao] = metodo;
                vezesCompressao++;

            }
            else if (opcao == 3){
                if (vezesCompressao < 3){
                    cout << endl << "É necessário comprimir pelo menos mais " << 3 - vezesCompressao << " vezes para gerar o arquivo de análise de compressão" << endl;
                }
                else{
                    // gera o saida.txt
                    gerenciador.escreveTaxaTXT(taxasCompressao, metodosTaxas, vezesCompressao);
                }
            }
            else{
                return 0;
            }
        }
        else{
            // ler N registros aleatórios dos arquivos
            cout << endl << "=============== MENU ===============" << endl;
            cout << endl << "ESCOLHA A OPÇÃO: " << endl;
            cout << "1. Comprimir arquivos texto " << endl;
            cout << "2. Analisar taxas de compressão " << endl;
            cout << "3. Sair" << endl;
            cout << "Escolha a opção: ";

            int opcao;
            cin >> opcao;

            if (opcao == 1){
                cout << endl << "ESCOLHA O MÉTODO DE COMPRESSÃO PARA OS REGISTROS" << endl;
                cout << "0. Huffman" << endl;
                cout << "1. LZ77" << endl;
                cout << "2. LZW" << endl;
                cout << "Escolha a opção: ";
                int metodo;
                cin >> metodo;
                cout << endl << "Comprimindo..." << endl;

                gerenciador.comprime(metodo);
                metodosTaxas[vezesCompressao] = metodo;
                taxasCompressao[vezesCompressao] = gerenciador.getTaxa();
                vezesCompressao++;
            }
            else if (opcao == 2){
                if (vezesCompressao < 3){
                    cout << endl << "É necessário comprimir pelo menos mais " << 3 - vezesCompressao << " vezes para gerar o arquivo de análise de compressão" << endl;
                }
                else{
                    // gera o saida.txt
                    gerenciador.escreveTaxaTXT(taxasCompressao, metodosTaxas, vezesCompressao);
                }
            }
            else {
                return 0;
            }

        }
    }
    
    return 0;
}