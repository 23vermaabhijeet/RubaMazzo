#ifndef CARTA_H
#define CARTA_H
#include <iostream>
#include <string>

using namespace std;

class Carta
{
    private:
        string seme, nome;
        int numero, punteggio;
    public:
        Carta();
        ~Carta();
        Carta(string seed, string name, int number, int point);
        void setSeme(string seed);
        void setNome(string name);
        void setNumero(int number);
        void setPunteggio(int point);
        int confronta(Carta c2, Carta briscola);
        int operator+(Carta c2);
        friend istream& operator>>(istream& in, Carta c);
        friend ostream& operator<<(ostream& out, const Carta c);
};

#endif // CARTA_H
