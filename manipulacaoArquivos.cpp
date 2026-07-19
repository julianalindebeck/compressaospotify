#include <dirent.h>
#include "manipulacaoArquivos.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>  
#include <iterator>
#include <cmath>

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

                linhasLidasConcatenadas += "\n" + nomeArquivo + ":\n\n";

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

                        linhasLidasConcatenadas += "\n";

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
        return novaDescompressao.descompressao(str);
    }
    else if (metodo == 1){
        LZ77 novaDescompressao;
        return novaDescompressao.descomprime(str);
    }
    else{
        LZW novaDescompressao;
        return novaDescompressao.descomprime(str); 
    }
}

void manipulacaoArquivos::escreveBinario(string comprimida){
    string caminhoCompleto = string(arquivos) + "/spotifyComp.bin";

    ofstream arquivo_binario(caminhoCompleto.c_str(), ios::out | ios::binary);
    
    if (!arquivo_binario.is_open()) {
        cerr << endl << "Erro ao abrir o arquivo para escrita binária em: " << caminhoCompleto << endl;
        return;
    }
    
    arquivo_binario.write(comprimida.data(), comprimida.size());
    arquivo_binario.close();
    
    cout << endl << "Arquivo binário gravado com sucesso em: " << caminhoCompleto << endl;

}

void manipulacaoArquivos::comprime(int metodo){
    // esse método que vai fazer tudo: pega o método, ai le os arquivos, pegando a string.
    string arquivosRecuperados = lerArquivoCompressao(arquivos, n);
    // cout << "Recuperado dos arquivos: " << arquivosRecuperados << endl;
    // Usa o método para comprimir a string
    string comprimida = comprime(arquivosRecuperados, metodo);

    // cout << "Comprimida: " << comprimida;
    // dependendo do método, escrevemos as infos no arquivo antes sobre o método

    int tamanhoOriginal = arquivosRecuperados.size() * 8;
    int tamanhoComprimido;
    string infoMetodo;
    if (metodo == 0){
        // escrever o nome do método + a árvore no arquivo
        infoMetodo += "HUFFMAN\n";
        tamanhoComprimido = comprimida.size();
    }
    else if (metodo == 1){
        // escrever só o nome do método para descomprimir
        infoMetodo += "LZ77\n";

        int qtdTuplas = 0;
        int i = 0;
        while (i < comprimida.size()) {
            if (comprimida[i] == '(') {
                qtdTuplas++;
                i++; 
                while (i < comprimida.size() && comprimida[i] != ',') i++; 
                i++; 
                while (i < comprimida.size() && comprimida[i] != ',') i++; 
                i++; 
                if (i + 4 <= comprimida.size() && comprimida.substr(i, 4) == "null") {
                    i += 4;
                } else {
                    i++; 
                }
                i++; 
            } else {
                i++;
            }
        }

        tamanhoComprimido = qtdTuplas * 14;
    }
    else{
        // escrever o nome + a tabela no arquivo
        infoMetodo += "LZW\n";

        int qtdCodigos = 0;
        int totalElementosDicionario = 0;
        
        int posFimDic = comprimida.find("]\n");
        if (posFimDic != string::npos) {
            for (int i = 0; i < posFimDic; i++) {
                if (comprimida[i] == '(') {
                    totalElementosDicionario++;
                }
            }
            
            for (int i = posFimDic + 2; i < comprimida.size(); i++) {
                if (comprimida[i] == '(') {
                    qtdCodigos++;
                }
            }
        }

        int bitsPorCodigo = 8; 
        if (totalElementosDicionario > 256) {
            bitsPorCodigo = (int)ceil(log2(totalElementosDicionario));
        }

        tamanhoComprimido = qtdCodigos * bitsPorCodigo;
    }

    infoMetodo += comprimida;
   
    // taxa compressao 
    
    taxa = (1.0 - (float)tamanhoComprimido / tamanhoOriginal) * 100;

    // escrevemos o arquivo binário com a compressao da string concatenada
    // salva o arquivo .bin no diretório
    escreveBinario(infoMetodo);

}

float manipulacaoArquivos::getTaxa(){
    return taxa;
}

void manipulacaoArquivos::escreveTaxaTXT(float taxas[], int metodos[], int vezes){
    string caminhoCompleto = string(arquivos) + "/saida.txt";
    ofstream meuArquivo(caminhoCompleto.c_str());

    if (meuArquivo.is_open()) {
        float somaTaxas = 0;
        meuArquivo << "================================= ANÁLISE DE TAXAS DE COMPRESSÃO ==================================\n";
        for (int i = 0; i < vezes; i++){
            somaTaxas += taxas[i];
            meuArquivo << "========== TAXA " << i + 1 << " ==========\n";
            meuArquivo << "Taxa de compressão: " << fixed << setprecision(2) << taxas[i] << "%\n";
            if (metodos[i] == 0){
                meuArquivo << "Método de compressão utilizado: HUFFMAN\n";
            }
            else if (metodos[i] == 1){
                meuArquivo << "Método de compressão utilizado: LZ77\n";
            }
            else{
                meuArquivo << "Método de compressão utilizado: LZW\n";
            }
        }
        // taxa media final

        meuArquivo << "========== TAXA MÉDIA ==========\n";
        meuArquivo << "Taxa de compressão média das " << vezes << " compressões: " << fixed << setprecision(2) << somaTaxas/vezes << "%\n";       

        meuArquivo.close();
        cout << endl << "Arquivo gravado com sucesso!" << endl;
    } else {
        cout << endl << "Erro ao abrir o arquivo." << endl;
    }
}

void manipulacaoArquivos::tipoDescompressao(){
    string caminhoCompleto = string(arquivos) + "/spotifyComp.bin";

    ifstream arquivo_binario(caminhoCompleto.c_str(), ios::in | ios::binary);

    if (!arquivo_binario.is_open()) {
        cerr << endl << "Erro ao abrir o arquivo binario para leitura!" << endl;
        return;
    }

    string metodo;
    getline(arquivo_binario, metodo); 

    arquivo_binario.close();

    if (metodo == "HUFFMAN") {
        descomprime(0);
    } 
    else if (metodo == "LZ77") {
        descomprime(1);
    } 
    else{
        descomprime(2);
    } 

}

void manipulacaoArquivos::descomprime(int metodo){
    // esse método que vai fazer tudo
    string caminhoCompleto = string(arquivos) + "/spotifyComp.bin";

    ifstream arquivo_binario(caminhoCompleto.c_str(), ios::in | ios::binary);

    if (!arquivo_binario.is_open()) {
        cerr << endl << "Erro ao abrir o arquivo binario para leitura!" << endl;
        return;
    }

    arquivo_binario.ignore(20, '\n');

    if (metodo == 0){
        // descomprime por huffman
        cout << endl << "DESCOMPRIMINDO POR HUFFMAN..." << endl;
        // precisa pegar a árvore passada e dps descomprimir
        string dadosComprimidos((istreambuf_iterator<char>(arquivo_binario)), istreambuf_iterator<char>());
        string dadosDescomprimidos = descomprime(dadosComprimidos, 0);
        escreveDescompressaoTXT(dadosDescomprimidos, 0);
    }
    else if (metodo == 1){
        // descomprime por LZ77
        cout << endl << "DESCOMPRIMINDO POR LZ77..." << endl;
        string dadosComprimidos((istreambuf_iterator<char>(arquivo_binario)), istreambuf_iterator<char>());
        string dadosDescomprimidos = descomprime(dadosComprimidos, 1);
        escreveDescompressaoTXT(dadosDescomprimidos, 1);
    }
    else{
        // descomprime por LZW
        cout << endl << "DESCOMPRIMINDO POR LZW..." << endl;
        // precisa pegar a tabela usada e depois descomprimir
        string dadosComprimidos((istreambuf_iterator<char>(arquivo_binario)), istreambuf_iterator<char>());
        string dadosDescomprimidos = descomprime(dadosComprimidos, 2);
        escreveDescompressaoTXT(dadosDescomprimidos, 2);
    }

    arquivo_binario.close();
}

void manipulacaoArquivos::escreveDescompressaoTXT(string dadosEscrever, int metodo){
    string caminhoCompleto = string(arquivos) + "/spotifyDesc.txt";
    ofstream meuArquivo(caminhoCompleto.c_str());

    if (meuArquivo.is_open()) {
        float somaTaxas = 0;
        meuArquivo << "================================= DADOS DESCOMPRIMIDOS ==================================\n";
        if (metodo == 0){
            meuArquivo << "Método de descompressão utilizado: HUFFMAN\n";
        }
        else if (metodo == 1){
            meuArquivo << "Método de descompressão utilizado: LZ77\n";
        }
        else{
            meuArquivo << "Método de descompressão utilizado: LZW\n";
        }

        meuArquivo << dadosEscrever;

        meuArquivo << "\n================================= FIM DESCOMPRESSÃO ==================================\n";
        
        meuArquivo.close();
        cout << endl << "Arquivo gravado com sucesso!" << endl;
    } else {
        cout << endl << "Erro ao abrir o arquivo." << endl;
    }

}