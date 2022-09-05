
#include "c_hamming.h"

#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <map>
#include <forward_list>

#include <algorithm>

/// @todo Вынести кудой-то...
static inline int pow2( int x )
{
    return 1 << x;
}

cHamming::cHamming()
{

}

/// @todo Разделить это на приватные методы
cHamming::sHammingMessage cHamming::code( sHammingMessage message )
{
    /// @todo Проверки std::static_assert

    // Поиск минимального количества контрольных бит
    int minCtrlBitCount = findMinCntrlBit( message );


    // "Сырые" пользовательские данные
    boost::dynamic_bitset<> rawData( message.mInfoLength, message.mMessage );

    // Длина закодированного блока
    const int codeBlockSize = message.mInfoLength + minCtrlBitCount;
    std::cout << "rawData = " << rawData << std::endl;



    // Контейнер для закодированного сообщения
    boost::dynamic_bitset<> codeBlock( codeBlockSize );


    // Поиск позиций контрольных бит
    std::set< int > cntrlBitPos( findCntrlBitPositions( minCtrlBitCount ) );

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

    /// @todo map cntrl to info...
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




    return sHammingMessage{ static_cast<int>(codeBlock.to_ulong()),
                static_cast<int>(codeBlock.size()) };
}

cHamming::sHammingMessage cHamming::decode( cHamming::sHammingMessage codeMess )
{
    // Поиск минимального количества контрольных бит
    int minCtrlBitCount = findMinCntrlBit( codeMess );

    // Поиск позиций контрольных бит
    std::set< int > cntrlBitPos( findCntrlBitPositions( minCtrlBitCount ) );


    // Контейнер для закодированного сообщения
    boost::dynamic_bitset<> codeBlock( codeMess.mInfoLength, codeMess.mMessage );


    std::map<int, std::forward_list< int > > infoBit2CntrlBits;
    // Поиск групп для информационных бит
    for( int idx = 0;
         idx < codeMess.mInfoLength;
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

    /// @todo Поиск неисправного бита. Синдром ошибки
    std::set<int> errorBits;
    std::cout << "Checking...\n";
    for( const auto & cntrlBit : cntrlBitPos )
    {
        int sum = codeBlock[ cntrlBit ];
        for( const auto & check : infoBit2CntrlBits )
        {
            /// @todo Массив + бинарный поиск
            if( check.second.end() !=
                    std::find( check.second.begin(), check.second.end(), cntrlBit ) )
            {
                sum ^= codeBlock[ check.first ];
            }
        }
        std::cout << "CntrlBit " << cntrlBit << " --- " << sum << std::endl;
        if( sum )
        {
            errorBits.insert( cntrlBit );
        }
    }


    std::cout << "Before " << codeBlock << std::endl;
    // Поиск ошибочного бита
    int errBit = 0;
    for( const auto & err : errorBits )
    {
        errBit += pow2( err ) - 1;
    }

    if( errorBits.size() )
    {
        std::cout << "Help it..." << errBit << " \n";
        codeBlock[ errBit ].flip();
    }

    std::cout << "After " << codeBlock << std::endl;



    // Удаление контрольных бит
    boost::dynamic_bitset<> messageBlock;//( codeMess.mInfoLength - cntrlBitPos.size() );
    for( int idx = 0;
         idx < codeMess.mInfoLength;
         ++idx )
    {
        // Именно информационный
        if( cntrlBitPos.end() == cntrlBitPos.find( idx ) )
        {
            messageBlock.push_back( codeBlock[ idx ] );
        }
    }


    std::cout << std::endl;


    return sHammingMessage{ static_cast<int>(messageBlock.to_ulong()),
                static_cast<int>(messageBlock.size()) };
}




// private

int cHamming::findMinCntrlBit( const cHamming::sHammingMessage &mess )
{
    /// @todo Почему -1 описать
    int minCtrlBitCount = 1;
    while( minCtrlBitCount > ( pow2(minCtrlBitCount) - mess.mInfoLength - 1 ) )
        ++minCtrlBitCount;

    return minCtrlBitCount;
}

std::set<int> cHamming::findCntrlBitPositions( int minCtrlBitCount )
{
    std::cout << "Позиции контрольных бит: ";
    std::set< int > cntrlBitPos;
    for( int idx = 0, cntrlPos = 1;
         idx < minCtrlBitCount;
         ++idx, cntrlPos = pow2( idx ) )
    {
        cntrlBitPos.insert( cntrlPos - 1 );
    }

    /// @test
    for( const auto & i : cntrlBitPos )
        std::cout << i << " ";

    return cntrlBitPos;
}
