#ifndef NAPOLETANO_H
#define NAPOLETANO_H
#include "mazzoDiCarte.h"

class Napoletano : public MazzoDiCarte
{
    public:
        Napoletano();
        ~Napoletano();
        Carta operator--();
        int cartePresenti();
        void inzializza();
};

#endif // NAPOLETANO_H
