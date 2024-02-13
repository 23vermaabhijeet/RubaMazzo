#include "napoletano.h"
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

Napoletano::Napoletano()
{
    dim = 40;
    delete[] c;
    c = new Carta[dim];
    inzializza();
}

Napoletano::~Napoletano()
{
}

Carta Napoletano::operator--(){
    int num = 0;
    num = rand() % dim;
    cout << endl << num;
    Carta res = c[num];

    for(int i = num; i < dim - 1; i++){
        c[i] = c[i + 1];
    }
    Carta *tmp = new Carta[--dim];
    for(int i = 0; i < dim; i++){
        tmp[i] = c[i];
    }

    delete[] c;
    c = new Carta[dim];
    for(int i = 0; i < dim; i++){
        c[i] = tmp[i];
    }
    delete[] tmp;
    return res;
}

int Napoletano::cartePresenti(){
    return dim;
}

void Napoletano::inzializza(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            if(i == 0)
                c[(i * 10) + j].setSeme("Spade");
            else if(i == 1)
                c[(i * 10) + j].setSeme("Bastoni");
            else if(i == 2)
                c[(i * 10) + j].setSeme("Denari");
            else if(i == 3)
                c[(i * 10) + j].setSeme("Coppe");

            c[(i * 10) + j].setNumero(j + 1);
            switch(j + 1){
                case 1:
                    c[(i * 10) + j].setPunteggio(11);
                    c[(i * 10) + j].setNome("Asso");
                    break;
                case 2:
                    c[(i * 10) + j].setPunteggio(0);
                    c[(i * 10) + j].setNome("DUE");
                    break;
                case 3:
                    c[(i * 10) + j].setPunteggio(10);
                    c[(i * 10) + j].setNome("TRE");
                    break;
                case 4:
                    c[(i * 10) + j].setPunteggio(0);
                    c[(i * 10) + j].setNome("QUATTRO");
                    break;
                case 5:
                    c[(i * 10) + j].setPunteggio(0);
                    c[(i * 10) + j].setNome("CINQUE");
                    break;
                case 6:
                    c[(i * 10) + j].setPunteggio(0);
                    c[(i * 10) + j].setNome("SEI");
                    break;
                case 7:
                    c[(i * 10) + j].setPunteggio(0);
                    c[(i * 10) + j].setNome("SETTE");
                    break;
                case 8:
                    c[(i * 10) + j].setPunteggio(2);
                    c[(i * 10) + j].setNome("Fante");
                    break;
                case 9:
                    c[(i * 10) + j].setPunteggio(3);
                    c[(i * 10) + j].setNome("Cavallo");
                    break;
                case 10:
                    c[(i * 10) + j].setPunteggio(4);
                    c[(i * 10) + j].setNome("Re");
                    break;
            }
        }
    }
}
