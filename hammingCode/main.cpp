#include <iostream>
#include <boost/dynamic_bitset.hpp>


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

    boost::dynamic_bitset<> rawData( infoBlockLength, 0xAF );

    // Длина закодированного блока
    const int codeBlockSize = infoBlockLength + minCtrlBitCount;

    std::cout << "rawData = " << rawData << std::endl;

    /// @todo boost::dynamic_bitset
    boost::dynamic_bitset<> codeBlock( codeBlockSize );


    // Все биты, порядковые номера которых являются степенью двойки - контрольные
    std::cout << "Позиции контрольных бит: ";
    for( int crntPos = 0, cntrlPos = 0;
         crntPos < minCtrlBitCount;
         ++crntPos, cntrlPos = pow2(crntPos) )
    {
        // Заполнение бит данных
        while( crntPos != cntrlPos )
        {
            codeBlock[ crntPos++ ] = rawData[ 0 ];
            rawData >>= 1;
        }

        std::cout << cntrlPos << " ";

        /// @todo Контрольные биты
        //codeBlock[ cntrlPos ] = 0;
    }

    std::cout << std::endl << "codeBlock = " << codeBlock << std::endl;

    std::cout << std::endl;




    return 0;
}
