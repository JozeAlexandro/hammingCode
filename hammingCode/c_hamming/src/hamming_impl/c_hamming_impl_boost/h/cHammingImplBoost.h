#ifndef CHAMMINGIMPLBOOST_H
#define CHAMMINGIMPLBOOST_H

#include "cHammingImplIface.h"

template < typename T_MESSAGE >
class cHammingImplBoost : public cHammingImplIface
{
public:

/* --- Реализация интерфейса ------------------------------------------------ */
public:
    virtual T_MESSAGE code(T_MESSAGE message) const override;
    virtual T_MESSAGE decode(T_MESSAGE codeMess) const override;
};

#endif // CHAMMINGIMPLBOOST_H
