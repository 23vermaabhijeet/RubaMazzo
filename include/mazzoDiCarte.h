#ifndef MAZZODICARTE_H
#define MAZZODICARTE_H
#include "carta.h"

class MazzoDiCarte
{
    protected:
        int dim;
        Carta *c;

    public:
        MazzoDiCarte();
        virtual ~MazzoDiCarte();
        virtual void inzializza() = 0;
};

#endif // MAZZODICARTE_H
