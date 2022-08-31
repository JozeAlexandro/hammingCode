#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <map>
#include <forward_list>
#include <set>
#include <algorithm>

// http://all-ht.ru/inf/systems/p_0_14.html

static inline int pow2( int x )
{
    return 1 << x;
}


int main()
{
    // Длина информационного блока
    int infoBlockLength{7};

    // Минимальное количество контрольных бит
    int minCtrlBitCount = 1;

    while( minCtrlBitCount > ( pow2(minCtrlBitCount) - infoBlockLength - 1 ) )
        ++minCtrlBitCount;

    boost::dynamic_bitset<> rawData( infoBlockLength, 0x4D );

    // Длина закодированного блока
    const int codeBlockSize = infoBlockLength + minCtrlBitCount;

    std::cout << "rawData = " << rawData << std::endl;

    /// @todo boost::dynamic_bitset
    boost::dynamic_bitset<> codeBlock( codeBlockSize );





    // Поиск позиций контрольных бит
    std::cout << "Позиции контрольных бит: ";
    std::set< int > cntrlBitPos;
    for( int idx = 0, cntrlPos = 1;
         idx < minCtrlBitCount;
         ++idx, cntrlPos = pow2( idx ) )
    {
        cntrlBitPos.insert( cntrlPos - 1 );
    }

    for( const auto & i : cntrlBitPos )
        std::cout << i << " ";


    std::map<int, std::forward_list< int > > infoBit2CntrlBits;

    // Поиск групп для информационных бит
    for( int idx = 0;
         idx < codeBlockSize;
         ++idx )
    {
        // Именно информационный
        if( cntrlBitPos.end() == cntrlBitPos.find( idx ) )
        {
            std::forward_list< int > crntCntrlPosBits;
            int infoPos = idx + 1;
            int cntrlCrntPos = 0;
            while( infoPos )
            {
                if( 1 & infoPos )
                {
                    crntCntrlPosBits.emplace_front( pow2( cntrlCrntPos ) - 1 );
                }

                cntrlCrntPos++;
                infoPos >>= 1;
            }

            infoBit2CntrlBits[ idx ] = crntCntrlPosBits;
        }
    }


    // Заполнение сообщения данными
    std::cout << std::endl;
    for(auto & it : infoBit2CntrlBits)
    {
        std::cout << "Inf: " << it.first << " --- Cntrl: ";
        for(auto &v : it.second)
            std::cout << v  << " ";
        std::cout << std::endl;

        static int idxRawMsg = 0;
        codeBlock[ it.first ] = rawData[ idxRawMsg++ ];
    }

    // Заполнение сообщения контрольными битами
    for( const auto & cntrlBit : cntrlBitPos )
    {
        int sum = 0;
        for( const auto & check : infoBit2CntrlBits )
        {
            /// @todo Массив + бинарный поиск
            if( check.second.end() !=
                    std::find( check.second.begin(), check.second.end(), cntrlBit ) )
            {
                sum ^= codeBlock[ check.first ];
            }
        }
        codeBlock[ cntrlBit ] = sum;
    }


    std::cout << std::endl << "codeBlock = " << codeBlock << std::endl;

    std::cout << std::endl;








    return 0;
}
