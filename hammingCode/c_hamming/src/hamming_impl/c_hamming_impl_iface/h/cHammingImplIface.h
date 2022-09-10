#ifndef CHAMMINGIMPLIFACE_H
#define CHAMMINGIMPLIFACE_H


/** ****************************************************************************
 * @file
 * @ group
 * @ etc
 * ****************************************************************************/

#include "c_hamming_message_iface.h"

/** ****************************************************************************
 * @brief Класс, предоставляющий интерфейс к реализациям
 * кодирования/декодирования Хэмминга
 * @details
 * @class cHammingImplIface
 * ****************************************************************************/
template < typename T_MESSAGE >
class cHammingImplIface
{
public:
    virtual ~cHammingImplIface();

    /// @brief Метод кодирования сообщения по методу Хэмминга.
    /// @details наименьший кол-во...
    /// @param @todo
    /// @return Закодированное сообщение
    virtual T_MESSAGE code( T_MESSAGE message ) const = 0;

    virtual T_MESSAGE decode( T_MESSAGE codeMess ) const = 0;
};

template < typename T_MESSAGE >
cHammingImplIface<T_MESSAGE>::~cHammingImplIface() {}


#endif // CHAMMINGIMPLIFACE_H
