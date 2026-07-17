#ifndef LZW_H__
#define LZW_H__
#include <string>
using namespace std;

class LZW
{
    private:
        int* codigo;
        string* dic;
        int tamDic = 0;
        int tamCod = 0;
        int capacidadeDic = 1000;
        int capacidadeCod = 1000;
    public:
        LZW();
        ~LZW();
        string comprime(string str);
        string descomprime(string str);
        void aumentaDic();
        void aumentaCod();
};

#endif