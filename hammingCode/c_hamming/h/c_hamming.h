#ifndef CHAMMING_H
#define CHAMMING_H

/** ****************************************************************************
 * @file
 * @ group
 * @ etc
 * ****************************************************************************/

#include <boost/dynamic_bitset.hpp>
#include <set>

/// @todo static methods
/// @todo singleton

/** ****************************************************************************
 * @brief Класс, реализующий кодирование-декодирование Хэмминга
 * @details
 * @class cHamming
 * ****************************************************************************/
class cHamming
{
/* --- Типы данных ---------------------------------------------------------- */
    public:


/* --- Открытые методы ------------------------------------------------------ */
public:
    /// @brief Метод кодирования сообщения по методу Хэмминга.
    /// @details Использует минимальное количество контрольных бит
    /// @param @todo
    /// @return Закодированное сообщение
    boost::dynamic_bitset<> code( const boost::dynamic_bitset<> &rawData ) const;

    boost::dynamic_bitset<> decode( const boost::dynamic_bitset<> &codeBlock ) const;




/* --- Закрытые методы ------------------------------------------------------ */
private:
    /// @brief Поиск минимального количества контрольных бит
    int findMinCntrlBit( const boost::dynamic_bitset<> &mess ) const;

    /// @brief Поиск позиций контрольных бит
    ///
    ///
    std::set< int > findCntrlBitPositions( int minCtrlBitCount ) const;
};

#endif // CHAMMING_H
