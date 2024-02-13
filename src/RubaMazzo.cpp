#include "RubaMazzo.h"
#include <ctime>

using namespace std;
RubaMazzo::RubaMazzo(){
    carteMazzo = nullptr;
    manoG1 = nullptr;
    manoG2 = nullptr;
    mazzoG1 = nullptr;
    mazzoG2 = nullptr;
    centro = nullptr;
    dim = new int[6] {40, 0, 0, 0, 0, 0};
}

RubaMazzo::~RubaMazzo(){
    delete[] carteMazzo;
    delete[] manoG1;
    delete[] manoG2;
    delete[] mazzoG1;
    delete[] mazzoG2;
    delete[] centro;
}

void RubaMazzo::startGame() {
    initialize();
    switch (typeGame()) {
        case 1:
            giocatoreVsGiocatore();
            break;
        case 2:
            giocatoreVsComputer();
            break;
    }
}
bool RubaMazzo::isPresent(int elem, int *mazzo, int dim){
    int i = 0;
    while(i < dim && elem != mazzo[i])
        i++;
    if(i < dim)
        return true;
    return false;
}

void RubaMazzo::initialize(){
    srand(time(NULL));
    int num = 0;
    carteMazzo = new int[40];
    for(int i = 0; i < 40; i++){
        do{
            num = rand() % 40;
        } while(isPresent(num, carteMazzo, i));
        carteMazzo[i] = num;
    }
}

int RubaMazzo::removeElem(int *mazzo, int numMazzo){
    int ris = -1;
    if(dim[numMazzo] > 0){
        ris = mazzo[0];
        for(int i = 0; i < dim[numMazzo] - 1; i++){
            mazzo[i] = mazzo[i + 1];
        }

        int *tmp = new int[--dim[numMazzo]];
        for(int i = 0; i < dim[numMazzo]; i++){
            tmp[i] = mazzo[i];
        }
        delete[] mazzo;
        mazzo = new int[dim[numMazzo]];
        for(int i = 0; i < dim[numMazzo]; i++){
            mazzo[i] = tmp[i];
        }
    }
    return ris;
}

void RubaMazzo::add(int *mazzo, int numMazzo, int elem){

    if(dim[numMazzo] < 40){
        int *tmp = new int[dim[numMazzo]];
        for(int i = 0; i < dim[numMazzo]; i++){
            tmp[i] = mazzo[i];
        }
        delete[] mazzo;
        mazzo = new int[++(dim[numMazzo])];
        for(int i = 0; i < dim[numMazzo] - 1; i++){
            mazzo[i] = tmp[i];
        }
        mazzo[dim[numMazzo] - 1] = elem;
        delete[] tmp;
    } else {
        cout << endl << "Non e' possibile";
    }
}


int RubaMazzo::typeGame() {
    int choice = 0;

    do {
        cout << endl << "SCEGLIERE MODALITA' DI GIOCO:" << endl;
        cout << endl << "\t[ 1 ]. Giocatore 1 VS Giocatore 2";
        cout << endl << "\t[ 2 ]. Giocatore 1 VS Computer" << endl;
        cout << endl << "Inserire il codice della scelta: ";
        cin >> choice;
    } while (choice < 1 || choice > 2);

    return choice;
}


void RubaMazzo::print(int *mazzo, int numMazzo){
    cout << endl << endl << "dim: " << dim[numMazzo];
    for(int i = 0; i < dim[numMazzo]; i++){
        cout << endl << i + 1 << ": "  << c[mazzo[i]];
    }
}


void RubaMazzo::printMazzi(){
    cout << endl << "\n\n\nCarte giocatore 1:";
    print(manoG1, 4);

    cout << endl << "\n\n\nCentro:";
    print(centro, 1);


    cout << endl << "\n\n\nCarte giocatore 2:";
    print(manoG2, 5);

    cout << endl << "\n\n\n\nDim mazzo: " << dim[0];
}

//GIOCO

void RubaMazzo::inizio(){
    centro = new int[4];
    dim[1] = 4;

    giocatore();
    computer();
    for(int i = 0; i < dim[1]; i++){
        centro[i] = removeElem(carteMazzo, 0);
    }
    ricarica();
}

void RubaMazzo::ricarica(){
    manoG1 = new int[3];
    dim[4] = 3;
    for(int i = 0; i < dim[4]; i++){
        manoG1[i] = removeElem(carteMazzo, 0);
    }


    manoG2 = new int[3];
    dim[5] = 3;
    for(int i = 0; i < dim[5]; i++){
        manoG2[i] = removeElem(carteMazzo, 0);
    }
}

int searchCentro(int elem){
    int i = 0;
    while(i < dim[1] && elem != centro[i]){
        i++;
    }
    if(i < dim)
        return i;
    return -1;
}

void removeCentroAddinMazzo(int *mazzo, int numMazzo, int pos){
    //da implementare
}

void tentativo(int* mazzo, int numMazzo, int elem){
    if()
}

void RubaMazzo::giocatore() {

}

void RubaMazzo::computer() {

}

void RubaMazzo::giocatoreVsComputer(){
    inizio();
    printMazzi();

}

void RubaMazzo::giocatoreVsGiocatore(){

}



