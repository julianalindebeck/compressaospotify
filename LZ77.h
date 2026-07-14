#ifndef LZ77_H__
#define LZ77_H__
#include "CodigoLZ77.h"
#include <string>

class LZ77
{
    private:
        int nb;
        int nd;
    public:
        LZ77();
        ~LZ77();
        string comprime(string str);
        string descomprime(string str);
};

#endif