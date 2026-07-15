#ifndef LZW_H__
#define LZW_H__
#include <string>
using namespace std;

class LZW
{
    private:
        int codigo[1000];
        string dic[1000];
        int tamDic = 0;
    public:
        LZW();
        ~LZW();
        string comprime(string str);
        string descomprime(string str);
};

#endif