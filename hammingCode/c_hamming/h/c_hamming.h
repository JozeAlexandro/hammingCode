#ifndef CHAMMING_H
#define CHAMMING_H

/** ****************************************************************************
 * @file
 * @ group
 * @ etc
 * ****************************************************************************/


#include <set>

/** ****************************************************************************
 * @brief Класс, реализующий кодирование-декодирование Хэмминга
 * @details
 * @class cHamming
 * ****************************************************************************/
class cHamming
{
/* --- Конструкторы/Деструкторы --------------------------------------------- */
public:
    cHamming();

/* --- Типы данных ---------------------------------------------------------- */
    public:

    ///
    struct sHammingMessage
    {
        int mMessage;
        int mInfoLength; /// @todo Не только info...
    };

/* --- Открытые методы ------------------------------------------------------ */
public:
    /// @brief Метод кодирования сообщения по методу Хэмминга.
    /// @details наименьший кол-во...
    /// @param @todo
    /// @return Закодированное сообщение
    sHammingMessage code( sHammingMessage message );

    sHammingMessage decode( sHammingMessage codeMess );




/* --- Закрытые методы ------------------------------------------------------ */
private:
    /// @brief Поиск минимального количества контрольных бит
    int findMinCntrlBit( const sHammingMessage& mess );

    /// @brief Поиск позиций контрольных бит
    ///
    ///
    std::set< int > findCntrlBitPositions( int minCtrlBitCount );
};

#endif // CHAMMING_H
