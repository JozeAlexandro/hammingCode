#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <map>
#include <forward_list>
#include <set>
#include <algorithm>


#include "c_hamming.h"

// http://all-ht.ru/inf/systems/p_0_14.html


/// @todo Реализовать через битовые маски
/// и напрямую. + pimpl

/// @todo logger
/// @todo Large message (more than sizeof(int)
/// @todo Дать возможность выбирать кол-во данных и кол-во контрольных бит

int main()
{
    cHamming hamming;
    cHamming::sHammingMessage codeMsg =
            hamming.code( cHamming::sHammingMessage{ 0x4d, 7 } );

    // Внесение ошибки
    codeMsg.mMessage = ( codeMsg.mMessage ^ 1 ) & 1;



    return 0;
}
