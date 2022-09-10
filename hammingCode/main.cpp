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

/// @todo Написать тест
static bool test( const cHamming &hamming, cHamming::sHammingMessage inVal );

int main()
{
    cHamming hamming;
    test( hamming , cHamming::sHammingMessage{ 0x4d, 7 } );

    return 0;
}

static bool test(const cHamming &hamming, cHamming::sHammingMessage inVal )
{
    std::cout << "Testing... " << inVal.mMessage << "( len = " << inVal.mInfoLength << " ):\n";
    bool result = true;
    const cHamming::sHammingMessage codeMsg = hamming.code( inVal );

    for( int errPos = 0; errPos < codeMsg.mInfoLength; ++errPos )
    {
        const bool revBit = !(codeMsg.mMessage & ( 1 << errPos ));
        cHamming::sHammingMessage errMsg = codeMsg;

        revBit ? errMsg.mMessage |= ( 1 << errPos )
               : errMsg.mMessage &= ~( 1 << errPos );

        cHamming::sHammingMessage decodeMsg = hamming.decode( errMsg );
        bool bTst = decodeMsg.mMessage == inVal.mMessage;
        std::cout << "errPos = " << errPos << " => " << bTst << std::endl;

        if( !bTst ) result = bTst;
    }

    return result;
}
