#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <map>
#include <forward_list>
#include <set>
#include <algorithm>



#include "c_hamming.h"

#include <boost/dynamic_bitset.hpp>


/// @todo logger
/// @todo doxy
/// @todo UML

static bool test( const cHamming &hamming, boost::dynamic_bitset<> &&msg );





int main()
{
    cHamming hamming;
    const bool isIntegral { test( hamming , boost::dynamic_bitset<>{ 6 * 8, 0x1234DEADBEEF } ) };

     std::cout << "Integral test = " << isIntegral << std::endl;
     return 0;
}

static bool test(const cHamming &hamming, boost::dynamic_bitset<> &&msg )
{
    std::cout << "Testing... " << msg << "( len = " << msg.size() << " ):\n";
    bool result = true;

    auto codeMsg = hamming.code( msg );

    for( unsigned errPos = 0; errPos < codeMsg.size(); ++errPos )
    {
        // Вносим ошибку
        codeMsg[ errPos ].flip();


        const auto decodeMsg = hamming.decode( codeMsg );
        const bool bTst = msg == decodeMsg;

        std::cout << "errPos = " << errPos << " Test's result " << bTst << std::endl;

        if( !bTst ) result = bTst;
        std::cout << "\n______________________________________\n";

        // Возврат в корректное состояние
        codeMsg[ errPos ].flip();
    }

    return result;
}
