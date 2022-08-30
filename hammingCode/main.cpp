#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <map>
#include <forward_list>

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


    std::map<int, std::forward_list< int > > infoBit2CntrlBits;


    // Заполнение информационными битами
    // Все биты, порядковые номера которых являются степенью двойки - контрольные
    std::cout << "Позиции контрольных бит: ";
    for( int crntPos = 0, cntrlPos = 0;
         crntPos < minCtrlBitCount;
         ++crntPos, cntrlPos = pow2(crntPos) )
    {
        // Заполнение бит данных
        while( crntPos != cntrlPos )
        {

            std::forward_list< int > crntCntrlPosBits;
            auto copyCrntPos(crntPos);

            for( int copyCrntPosIdx = 0;
                 copyCrntPos != 0;
                 copyCrntPos >>= 1, copyCrntPosIdx++ )
            {
                if( 1 & copyCrntPos )
                {
                    crntCntrlPosBits.push_front( copyCrntPosIdx );
                }
            }

            infoBit2CntrlBits[ crntPos ] = crntCntrlPosBits;


            codeBlock[ crntPos++ ] = rawData[ 0 ];
            rawData >>= 1;
        }

        std::cout << cntrlPos << " ";

        /// @todo Контрольные биты
        //codeBlock[ cntrlPos ] = 0;
    }
/*
    // Заполнение контрольными битами
    for( int crntPos = 0, cntrlPos = 0;
         crntPos < minCtrlBitCount;
         ++crntPos, cntrlPos = pow2(crntPos) )
    {
        while( crntPos != cntrlPos )
        {
            int copyCrnt = crntPos;
            while( copyCrnt )
            {

            }
        }
    }*/


    std::cout << std::endl << "codeBlock = " << codeBlock << std::endl;

    std::cout << std::endl;




    return 0;
}
