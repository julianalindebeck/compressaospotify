# Requisitos
- Compilador g++
- Sistema Linux ou terminal compatível (Git Bash, MSYS2 ou WSL no Windows)

# Compilação e execução 
No terminal, dentro da pasta do projeto, execute:
g++ main.cpp Huffman.cpp ListaSEncad.cpp No.cpp LZ77.cpp LZW.cpp manipulacaoArquivos.cpp -o programa

E logo em seguida (considere o caminho como um exemplo, e considere N como o número de registros aleatórios a serem recuperados dos arquivos):
./programa /diretorio/contendo/arquivos/ N
