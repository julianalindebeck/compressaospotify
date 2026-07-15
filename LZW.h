#ifndef LZW_H__
#define LZW_H__
#include "CodigoLZW.h"
#include <string>

class LZW
{
    private:
    
    public:
        LZW();
        ~LZW();
        string comprime(string str);
        string descomprime(string str);
};

#endif