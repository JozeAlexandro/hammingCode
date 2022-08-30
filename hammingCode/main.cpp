#include <iostream>
#include <boost/dynamic_bitset.hpp>

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



    // Длина закодированного блока
    const int codeBlockSize = infoBlockLength + minCtrlBitCount;

    std::cout << "codeBlockSize = " << codeBlockSize << std::endl;

    /// @todo boost::dynamic_bitset
    boost::dynamic_bitset<> codeBlock( codeBlockSize );


    // Все биты, порядковые номера которых являются степенью двойки - контрольные
    std::cout << "Позиции контрольных бит: ";
    for( int crntPos = 0, cntrlPos = 1;
         crntPos < minCtrlBitCount;
         ++crntPos, cntrlPos = pow2(crntPos) )
    {
        std::cout << cntrlPos << " ";
        codeBlock[ pow2( cntrlPos ) ] = 1;
    }

    std::cout << std::endl;




    return 0;
}
