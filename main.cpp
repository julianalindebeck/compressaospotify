#include <iostream>
#include <fstream>
#include <string>
#include "Huffman.h"
#include "LZ77.h"
#include "LZW.h"
#include "manipulacaoArquivos.h"
using namespace std;

string comprime(string str, int metodo){
    if (metodo == 0){
        Huffman* novaCompressao = new Huffman();
        return novaCompressao->constroi(str);
    }
    else if (metodo == 1){
        LZ77* novaCompressao = new LZ77();
        return novaCompressao->comprime(str);
    }
    else{
        LZW* novaCompressao = new LZW();
        return novaCompressao->comprime(str);
    }
}

string descomprime(string str, int metodo){
    if (metodo == 0){
        Huffman* novaDescompressao = new Huffman();
        return novaDescompressao->descompressao(novaDescompressao->constroi(str));
    }
    else if (metodo == 1){
        LZ77* novaDescompressao = new LZ77();
        return novaDescompressao->descomprime(str);
    }
    else if(metodo == 2){
        LZW* novaDescompressao = new LZW();
        return novaDescompressao->descomprime(novaDescompressao->comprime(str)); 
    }
    return "";
}

void comprime(int metodo){
    
}


void descomprime(int metodo){

}

int main(int argc, char *argv[]){

    int tamN = stoi(argv[2]);

    // ainda tem que fazer as estatísticas de desempenho

    while (true){
        cout << endl << "Lendo " << tamN << " registros aletórios dos arquivos..." << endl;

        // procurando os arquivos
        if(verBinario(argv[1])){
            // salvar os arquivos binários

            cout << endl << "=============== MENU ===============" << endl;
            cout << "ESCOLHA A OPÇÃO: " << endl;
            cout << "1. Descomprimir arquivo(s) binário(s) " << endl;
            cout << "2. Comprimir arquivos texto " << endl;
            cout << "3. Sair" << endl;
            cout << "Escolha a opção: ";
            int opcao;
            cin >> opcao;
            
            if (opcao == 1){
                // descomprime os arquivos e salva no diretorio (acho que tem que salvar no arquivo o método
                // tipo o HUFFMAN salvar a árvore, e no LZW salvar a nossa biblioteca)
            }
            else if (opcao == 2){
                cout << "ESCOLHA O MÉTODO DE COMPRESSÃO PARA OS REGISTROS" << endl;
                cout << "0. Huffman" << endl;
                cout << "1. LZ77" << endl;
                cout << "2. LZW" << endl;
                cout << "Escolha a opção: ";
                int metodo;
                cin >> metodo;

                string comprimida = comprime(lerArquivoCompressao(argv[1], tamN), metodo);
                // comprime e transforma em binário salvando na pasta (acho que tem que salvar o método no arquivo)

                // só nao entendi como usar a funcao void comprime.... e agr falta só salvar a compressao em um arquivo binário
            }
            else{
                return 0;
            }
        }
        else{
            // ler N registros aleatórios dos arquivos
            cout << endl << "=============== MENU ===============" << endl;
            cout << "ESCOLHA A OPÇÃO: " << endl;
            cout << "1. Comprimir arquivos texto " << endl;
            cout << "2. Sair" << endl;
            cout << "Escolha a opção: ";

            int opcao;
            cin >> opcao;

            if (opcao == 1){
                cout << "ESCOLHA O MÉTODO DE COMPRESSÃO PARA OS REGISTROS" << endl;
                cout << "0. Huffman" << endl;
                cout << "1. LZ77" << endl;
                cout << "2. LZW" << endl;
                cout << "Escolha a opção: ";
                int metodo;
                cin >> metodo;
                string comprimida = comprime(lerArquivoCompressao(argv[1], tamN), metodo);
                // comprime e transforma em binário salvando na pasta (acho que tem que salvar o método no arquivo)

                // só nao entendi como usar a funcao void comprime.... e agr falta só salvar a compressao em um arquivo binário
            }
            else {
                return 0;
            }

        }
    }



    // cout << endl << "=============== MENU ===============" << endl;
    // cout << "1. Comprimir uma string passada como parâmetro " << endl;
    // cout << "2. Descomprimir uma string passada como parâmetro " << endl;
    // cout << "3. Comprimir o conteúdo de um arquivo texto " << endl;
    // cout << "2. Descomprimir uma string passada como parâmetro " << endl;
    // cout << "Escolha a opção: ";
    
    // int opcao;
    // int metodo;
    // cin >> opcao;

    // if (opcao == 1){
    //     string str;
    //     cout << "Digite a string: ";
    //     cin >> str;

    //     cout << endl << "Agora escolha o método! " << endl;
    //     cout << "0. Huffman" << endl;
    //     cout << "1. LZ77" << endl;
    //     cout << "2. LZW" << endl;
    //     cout << "Escolha a opção: ";

    //     cin >> metodo;

    //     string stringComprimida = comprime(str, metodo);

    //     float taxaCompressao;

    //     cout << "String comprimida: " << stringComprimida << endl;
    //     int tamanhoCompressao;
    //     if (stringComprimida.length() % 8 == 0){
    //         tamanhoCompressao = stringComprimida.length()/8;
    //     }
    //     else{
    //         tamanhoCompressao = (stringComprimida.length()/8) + 1;
    //     }
    //     taxaCompressao = (float)(str.length() - tamanhoCompressao)/ str.length();
    //     cout << "Taxa de Compressão: " << taxaCompressao*100 << "%" << endl;

    //     if (metodo == 0 || metodo == 2){
    //         cout << endl << "Deseja descomprimir? (Y/N) ";
    //         char yn;
    //         cin >> yn;
    //         if (yn == 'Y' || yn == 'y'){
    //             cout << endl << "String descomprimida: " << descomprime(str, metodo) << endl;
    //         }
    //     }
        
    // }
    // else if(opcao == 2){
    //     string str;
    //     cout << "Digite a string: ";
    //     cin >> str;

    //     cout << endl << "Agora escolha o método! " << endl;
    //     cout << "1. LZ77" << endl;
    //     cout << "Escolha a opção: ";

    //     cin >> metodo;

    //     string stringDescomprimida = descomprime(str, metodo);

    //     cout << "String descomprimida: " << stringDescomprimida << endl;
    // }
    return 0;
}