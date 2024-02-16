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

int RubaMazzo::removeElem(int* &mazzo, int numMazzo, int pos){
    int ris = -1;
    if(dim[numMazzo] > 0){
        ris = mazzo[pos];
        for(int i = pos; i < dim[numMazzo] - 1; i++){
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

void RubaMazzo::add(int* &mazzo, int numMazzo, int elem){
    if(dim[numMazzo] < 40){
        int *tmp = new int[dim[numMazzo]];
        for(int i = 0; i < dim[numMazzo]; i++){
            tmp[i] = mazzo[i];
        }
        delete[] mazzo;
        ++dim[numMazzo];
        mazzo = new int[dim[numMazzo]];
        for(int i = 0; i < dim[numMazzo] - 1; i++){
            mazzo[i] = tmp[i];
        }
        mazzo[dim[numMazzo] - 1] = elem;
        delete[] tmp;
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


void RubaMazzo::print(int* &mazzo, int numMazzo){

    cout << endl;
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < dim[numMazzo]; i++){
            if(j == 0)
                cout << "\t| Nome: "  << c[mazzo[i]].getNome();
            else
                cout << "\t| Numero: "  << c[mazzo[i]].getNumero();
        }
        cout << endl;
    }
}


void RubaMazzo::printMazzi(int numMazzo){
    if(numMazzo == 2){
        cout << endl << "\nCarte giocatore 1:\n";
        print(manoG1, 4);
    }
    if(dim[2] > 0){
        cout << endl << "Mazzo giocatore 1:";
        cout << c[mazzoG1[dim[2]- 1]];
        cout << endl << "Carte presenti nel mazzo di giocatore: " << dim[2];
    }


    cout << endl << "\n-------------------------------------------------------------------------";

    cout << endl << "\nCentro:\n";
    print(centro, 1);

    cout << endl << "\n-------------------------------------------------------------------------";
    if(numMazzo == 3){
        cout << endl << "\nCarte giocatore 2:\n";
        print(manoG2, 5);
    }
    if(dim[3] > 0){
        cout << endl <<  "Mazzo giocatore 2:";
        cout <<  c[mazzoG2[dim[3]- 1]];
        cout << endl <<  "Carte presenti nel mazzo di giocatore: " << dim[3];
    }

}

//GIOCO

void RubaMazzo::inizio(){
    centro = new int[4];
    dim[1] = 4;
    int cont = 0;

    for(int i = 0; i < dim[1]; i++){
        centro[i] = removeElem(carteMazzo, 0, 0);
    }
    ricarica();
    int times = 0;
    while(times < 18){
        giocatore(manoG1, mazzoG1, 4, 2);
        giocatore(manoG2, mazzoG2, 5, 3);
        cont++;
        times++;
        if(cont == 3 && times < 18){
            ricarica();
            cont = 0;
        }
    }

    if(dim[1] > 0){
        int numCarte = dim[1];
        for(int i = 0; i < numCarte; i++){
            int card = removeElem(centro, 1, 0);
            add(mazzoG2, 3, card);
        }
    }

    system("cls");
    title();
    printMazzi(3);
    cout << endl << "\n\n\t\tCarte giocatore 1: " << dim[2];
    cout << endl << "\t\tCarte giocatore 2: " << dim[3];
    if(dim[2] > dim[3]){
        cout << endl << "\n\n\t\tHa vinto il giocatore 1\n\n";
    } else {
        cout << endl << "\n\n\t\tHa vinto il giocatore 2\n\n";
    }
}

void RubaMazzo::ricarica(){
    delete[] manoG1;
    manoG1 = new int[3];
    dim[4] = 3;
    for(int i = 0; i < dim[4]; i++){
        manoG1[i] = removeElem(carteMazzo, 0, 0);
    }


    delete[] manoG2;
    manoG2 = new int[3];
    dim[5] = 3;
    for(int i = 0; i < dim[5]; i++){
        manoG2[i] = removeElem(carteMazzo, 0, 0);
    }

}

int RubaMazzo::searchCentro(int elem){
    int i = 0;
    while(i < dim[1] && elem != c[centro[i]].getNumero()){
        i++;
    }
    if(i < dim[1])
        return i;
    return -1;
}

//restituisce true se ha trovato un carta simile in mazzo centrale e di conseguenza l'ha aggiungto in mazzoG$
//restituisce false se non a trovato una carta in mazzo centrale così ha tolto dalla mano di giocatore e ha aggiunto in mazzo centrale
bool RubaMazzo::removeCentroAddinMazzo(int* &mano, int* &mazzo, int numMano, int numMazzo, int pos, int* &mazzoPart, int numMazzoPart){

    int i = 0;
    i = searchCentro(c[mano[pos]].getNumero());
    if(i != -1){
        int card1 = removeElem(centro, 1, i);
        int card2 = removeElem(mano, numMano, pos);

        add(mazzo, numMazzo, card1);
        add(mazzo, numMazzo, card2);
        return true;
    } else {
        bool rubato = rubaMazzo(mazzoPart, numMazzoPart, c[mano[pos]].getNumero(), mazzo, numMazzo);
        if(rubato == false){
            int card1 = removeElem(mano, numMano, pos);
            add(centro, 1, card1);
        } else {
            int card1 = removeElem(mano, numMano, pos);
            add(mazzo, numMazzo, card1);
        }
        return false;
    }
}

bool RubaMazzo::rubaMazzo(int* &mazzo, int numMazzo, int scelta, int* &mazzoDest, int numDest){
    if(dim[numMazzo] > 0 && scelta == c[mazzo[dim[numMazzo] - 1]].getNumero()){
        int card = 0;
        cout << endl << "\t\t\t RUBA MAZZO!!! \n\n";
        int numCarte = dim[numMazzo];
        for(int i = 0; i < numCarte; i++){
            card = removeElem(mazzo, numMazzo, 0);
            add(mazzoDest, numDest, card);
        }
        system("pause");
        return true;
    }
    return false;
}

void tentativo(int *mazzo, int numMazzo, int elem){
    //if()
}

void RubaMazzo::giocatore(int* &mano, int* &mazzo, int numMano, int numMazzo) {
    int cartaScelta;
    bool cartaValida = false;

    system("cls");
    title();
    if(numMano == 4){
        cout << endl << "\nTurno giocatore 1" << endl;
    } else {
        cout << endl << "\nTurno giocatore 2" << endl;
    }

    printMazzi(numMazzo);
    do {
        cout << endl << "Scegliere una carta dal mazzo centrale (1-" << dim[numMano] << "): ";
        cin >> cartaScelta;
        cartaValida = (cartaScelta >= 1 && cartaScelta <= dim[numMano]);
        if (!cartaValida) {
            cout << endl << "Carta non valida. Riprova.";
        }
    } while (!cartaValida);


    cartaScelta--;
    if(numMazzo == 2){
        removeCentroAddinMazzo(mano, mazzo, numMano, numMazzo, cartaScelta, mazzoG2, 3);
    } else {
        removeCentroAddinMazzo(mano, mazzo, numMano, numMazzo, cartaScelta, mazzoG1, 2);
    }
}

void RubaMazzo::computer() {

}

void RubaMazzo::giocatoreVsComputer(){
    inizio();
}

void RubaMazzo::giocatoreVsGiocatore(){
    inizio();
}


























void RubaMazzo::title(){

    cout << endl << "\t8888888b.           888                    888b     d888";
    cout << endl << "\t888   Y88b          888                    8888b   d8888";
    cout << endl << "\t888    888          888                    88888b.d88888";
    cout << endl << "\t888   d88P 888  888 88888b.   8888b.       888Y88888P888  8888b.  88888888 88888888  .d88b.";
    cout << endl << "\t8888888P\"  888  888 888 \"88b     \"88b      888 Y888P 888     \"88b    d88P     d88P  d88\"\"88b";
    cout << endl << "\t888 T88b   888  888 888  888 .d888888      888  Y8P  888 .d888888   d88P     d88P   888  888";
    cout << endl << "\t888  T88b  Y88b 888 888 d88P 888  888      888   \"   888 888  888  d88P     d88P    Y88..88P";
    cout << endl << "\t888   T88b  \"Y88888 88888P\"  \"Y888888      888       888 \"Y888888 88888888 88888888  \"Y88P\"\n\n\n";

}


