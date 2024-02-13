#include "carta.h"
#include <iostream>
using namespace std;

Carta::Carta()
{
    seme = "unknown";
    nome = "unknown";
    numero = 0;
    punteggio = 0;
}

Carta::~Carta()
{
}

Carta::Carta(string seed, string name, int number, int point){
    seme = seed;
    if(seme.length() == 0)
        seme = "unknown";
    nome = name;
    if(nome.length() == 0)
        nome = "unknown";
    numero = number;
    if(numero < 0)
        numero = 0;
    punteggio = point;
    if(punteggio < 0)
        punteggio = 0;
}

void Carta::setSeme(string seed){
    seme = seed;
    if(seme.length() == 0)
        seme = "unknown";
}

void Carta::setNome(string name){
    nome = name;
    if(nome.length() == 0)
        nome = "unknown";
}

void Carta::setNumero(int number){
    numero = number;
    if(numero < 0)
        numero = 0;
}

void Carta::setPunteggio(int point){
    punteggio = point;
    if(punteggio < 0)
        punteggio = 0;
}

//ritorna 1 per l'istanza chiamante
// 2 per chiamata
int Carta::confronta(Carta c2, Carta briscola){
    int result = 0;
    if(seme == c2.seme){
        if(punteggio > c2.punteggio){
            result = 1;
        } else {
            result = 2;
        }
    } else if (seme == c2.seme && punteggio == c2.punteggio){
        if(numero > c2.numero)
            result = 1;
        else
            result = 2;
    } else if (seme != c2.seme){
        if(seme == briscola.seme)
            result = 1;
        else if (c2.seme == briscola.seme)
            result = 2;
        else
            result = 1;
    }
    return result;
}

int Carta::operator+(Carta c2){
    return (numero + c2.numero);
}

istream& operator>>(istream& in, Carta c){

    do{
        cout << endl << "Seme: ";
        in >> c.seme;
    } while(c.seme.length() == 0);
     do{
        cout << endl << "Nome: ";
        in >> c.nome;
    } while(c.nome.length() == 0);

     do{
        cout << endl << "Numero: ";
        in >> c.numero;
    } while(c.numero <= 0);

    do{
        cout << endl << "Punteggio: ";
        in >> c.punteggio;
    } while(c.punteggio <= 0);
    return in;
}


ostream& operator<<(ostream& out, const Carta c){
    cout << endl << "Seme: " << c.seme;
    cout << endl << "Nome: " << c.nome;
    cout << endl << "Numero: " << c.numero;
    cout << endl << "Punteggio: " << c.punteggio;
    return out;
}
