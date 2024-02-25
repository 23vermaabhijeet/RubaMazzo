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


//distruttore
RubaMazzo::~RubaMazzo(){
    delete[] carteMazzo;
    delete[] manoG1;
    delete[] manoG2;
    delete[] mazzoG1;
    delete[] mazzoG2;
    delete[] centro;
}


//metodi generali


int RubaMazzo::typeGame() {
    int choice = 0;

    do {
        cout << endl << "SCEGLIERE MODALITA' DI GIOCO:" << endl;
        cout << endl << "\t[ 1 ]. Giocatore 1 VS Giocatore 2";
        cout << endl << "\t[ 2 ]. Giocatore 1 VS Computer"<< endl;
        cout << "\t[ 3 ]. Visualizza regolamento" << endl;
        cout << endl << "Inserire il codice della scelta: ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return choice;
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
        case 3:
            viewRegolamento();
    }
}

//inizializza il mazzo principale (contenente 40 carte)
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


//metodo che cerca elem nel mazzo (passato come parametro)
bool RubaMazzo::isPresent(int elem, int *mazzo, int dim){
    int i = 0;
    while(i < dim && elem != mazzo[i]) // ricerca lineare
        i++;
    if(i < dim)
        return true;
    return false;
}


//rimuove la carta dal mazzo dal posizione passato come parametro
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


//aggiunge la carta in mazzo passato come parametro
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


//stampa tutte le carte del mazzo passato come parametro
void RubaMazzo::print(int* &mazzo, int numMazzo){
    cout << endl;
    for(int j = 0; j < 2; j++){
        cout << "\t";
        for(int i = 0; i < dim[numMazzo]; i++){
            textbackground(CYAN);
            if(j == 0)
                cout << "| Nome: "  << c[mazzo[i]].getNome();
            else {
                cout << "| Numero: "  << c[mazzo[i]].getNumero();
                (c[mazzo[i]].getNumero() >= 10) ? cout << "   " : cout << "    ";
            }
            textbackground(BLACK);
            cout << " ";
        }

        cout << endl;
    }
}


//metodo che estrae tre carte per ogni giocatore (due giocatori)
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

//metodo che cerca se l'elemento (cioè la carta) passata è presente nel mazzo sul tavolo
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
            system("pause");
        }
        return false;
    }
}


//metodo che ruba il mazzo, il mazzo può essere "Rubato" solo se la carta giocata sia uguale all'ultima carte presente nel
//mazzo del altro giocatore
bool RubaMazzo::rubaMazzo(int* &mazzo, int numMazzo, int scelta, int* &mazzoDest, int numDest){
    if(dim[numMazzo] > 0 && scelta == c[mazzo[dim[numMazzo] - 1]].getNumero()){
        int card = 0;
        cout << endl << "\t\t";
        textbackground(LIGHTMAGENTA);
        cout << "RUBA MAZZO!!!";
        textbackground(BLACK);
        cout << endl << "\n\n";
        int numCarte = dim[numMazzo];
        for(int i = 0; i < numCarte; i++){
            card = removeElem(mazzo, numMazzo, 0); // rimuove la carta dal mazzo di giocatore
            add(mazzoDest, numDest, card); // aggiunge la carta nel mazzo di altro giocatore
        }
        return true;
    }
    return false;
}

void RubaMazzo::giocatore(int* &mano, int* &mazzo, int numMano, int numMazzo) {
    int cartaScelta;
    bool cartaValida = false;

    if(numMano == 4){
        cout << endl << "\nTurno giocatore 1 " << endl;
    } else {
        cout << endl << "\nTurno giocatore 2 " << endl;
    }

    printMazzi(numMazzo);
    do {
        cout << endl << "Scegliere una carta dalla mano (1-" << dim[numMano] << "): ";
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











//Giocatore 1 vs giocatore 2


void RubaMazzo::printMazzi(int numMazzo){
    if(numMazzo == 2){
        cout << endl << "\nCarte giocatore 1:\n";
        print(manoG1, 4);
    }
    if(dim[2] > 0){
        textbackground(BROWN);
        textcolor(BLACK);
        cout << endl << " Mazzo giocatore 1:";
        cout << c[mazzoG1[dim[2]- 1]];
        textbackground(LIGHTGREEN);
        cout << endl << "Carte presenti nel mazzo di giocatore: " << dim[2];
        textcolor(WHITE);
        textbackground(BLACK);
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
        textbackground(BROWN);
        textcolor(BLACK);
        cout << endl << " Mazzo giocatore 2:";
        cout << c[mazzoG2[dim[3]- 1]];
        textbackground(LIGHTGREEN);
        cout << endl << "Carte presenti nel mazzo di giocatore: " << dim[3];
        textbackground(BLACK);
        textcolor(WHITE);

    }

}


void RubaMazzo::giocatoreVsGiocatore(){
    centro = new int[4];
    dim[1] = 4;
    int times = 6;

    for(int i = 0; i < dim[1]; i++){
        centro[i] = removeElem(carteMazzo, 0, 0);
    }

    for(int i = 0; i < times; i++){
        ricarica();
        for(int j = 0; j < 3; j++){
            system("cls");
            title(1);
            giocatore(manoG1, mazzoG1, 4, 2);
            system("cls");
            title(1);
            giocatore(manoG2, mazzoG2, 5, 3);
        }
    }

    if(dim[1] > 0){ // secondo le regole di Rubamazzo, le carte rimanenti sul tavolo vengono aggiunte nel mazzo di secondo giocatore
        int numCarte = dim[1];
        for(int i = 0; i < numCarte; i++){
            int card = removeElem(centro, 1, 0);
            add(mazzoG2, 3, card);
        }
    }

    system("cls");
    title(1);
    printMazzi(3);


    cout << endl << "\n\n\t\tCarte giocatore 1: " << dim[2];
    cout << endl << "\t\tCarte giocatore 2: " << dim[3] << endl;
    textbackground(LIGHTMAGENTA);
    if(dim[2] > dim[3]){ // la vittoria è definita dal numero di carte presenti nel mazzo di ogni giocatore
        cout << endl << "\n\t\tHa vinto il giocatore 1\n";
    } else if (dim[2] < dim[3]){
        cout << endl << "\n\t\tHa vinto il giocatore 2\n";
    } else {
        cout << endl << "\n\t\tNon ha vinto nessuno\n";
    }
    textbackground(BLACK);
    cout << endl;
}









//parte computer vs giocatore

void RubaMazzo::giocatoreVsComputer(){
    centro = new int[4];
    dim[1] = 4;
    int times = 6;

    for(int i = 0; i < dim[1]; i++){
        centro[i] = removeElem(carteMazzo, 0, 0);
    }

    for(int i = 0; i < times; i++){
        ricarica();
        for(int j = 0; j < 3; j++){
            system("cls");
            title(2);
            giocatore(manoG1, mazzoG1, 4, 2);
            system("cls");
            title(2);
            computer();
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
    title(2);
    printMazzi(3);
    cout << endl << "\n\n\t\tCarte Giocatore: " << dim[2];
    cout << endl << "\t\tCarte Computer: " << dim[3] << endl;
    textbackground(LIGHTMAGENTA);
    if(dim[2] > dim[3]){
        cout << endl << "\n\t\tHa vinto il giocatore\n";
    } else if (dim[2] < dim[3]){
        cout << endl << "\n\t\tHa vinto il computer\n";
    } else {
        cout << endl << "\n\t\tNon ha vinto nessuno\n";
    }
    textbackground(BLACK);
    cout << endl;
}



void RubaMazzo::computer(){
    cout << endl << "Turno computer\n";
    if(dim[2] > 0){
        cout << endl << "\nCarte di giocatore 1\n";
        textbackground(BROWN);
        textcolor(BLACK);
        cout << endl << " Mazzo giocatore:  ";
        cout << c[mazzoG1[dim[2] - 1]];
        textbackground(LIGHTGREEN);
        cout << endl << "Numero di carte presenti nel mazzo di giocatore: " << dim[2];
        textbackground(BLACK);
        textcolor(WHITE);
    }
    cout << endl << "\n--------------------------------------------\n";
    cout << endl << "\nCentro\n";
    print(centro, 1);

    if(dim[3] > 0){
        cout << endl << "--------------------------------------------";
        textbackground(BROWN);
        textcolor(BLACK);
        cout << endl << "\n Mazzo computer:   ";
        cout << c[mazzoG2[dim[3] - 1]];
        textbackground(LIGHTGREEN);
        cout << endl << "Numero di carte presenti nel mazzo di computer: " << dim[3];
        textbackground(BLACK);
        textcolor(WHITE);
    }

    cout << endl << "\nIl computer sta pensando.......\n";

    tryFindCarta();

}

//metodo che permette al computer di cercare una possibile carta confrontando le carte presenti nella mano con quelle sul tavolo
//se non trova nessuna carta sul tavolo, cerca anche di rubare il mazzo nel caso fosse possibile
void RubaMazzo::tryFindCarta(){
    srand(time(NULL));
    if(dim[5] > 0){
        int i = 0;
        int pos = 0;
        bool found = false, rubato = false;

        while(i < dim[5] && !found && !rubato){
            pos = searchCentro(c[manoG2[i]].getNumero());
            rubato = rubaMazzo(mazzoG1, 2, c[manoG2[i]].getNumero(), mazzoG2, 3);
            if(pos != -1){
                found = true;
            }
            i++;
        }
        i--;
        if(i < dim[5] && found && !rubato){
            int card1 = removeElem(centro, 1, pos);
            int card2 = removeElem(manoG2, 5, i);

            add(mazzoG2, 3, card1);
            add(mazzoG2, 3, card2);
            cout << endl << "Il computer ha trovato una carta simile\n";
        } else {
            if(rubato){  // se è riuscito a rubare il mazzo, aggiunge anche la carta presente nella mano, grazie a cui è riuscito a rubare, nel proprio mazzo
                int card1 = removeElem(manoG2, 5, i);
                add(mazzoG2, 3, card1);
                cout << endl << "Il computer ha rubato il mazzo\n";
            } else { // se non ha potuto rubare il mazzo genera una carta casuale e lo aggiunge nel mazzo centrale
                int card = rand() % dim[5];
                int card1 = removeElem(manoG2, 5, card);
                add(centro, 1, card1);
                cout << endl << "Il computer non ha trovato niente\n";
            }
        }
    }
    system("pause");
}





















//stampa regolamento e titolo

void RubaMazzo::title(int num){

    textcolor(LIGHTRED);
    cout << endl << "\t8888888b.           888                    888b     d888";
    cout << endl << "\t888   Y88b          888                    8888b   d8888";
    cout << endl << "\t888    888          888                    88888b.d88888";
    cout << endl << "\t888   d88P 888  888 88888b.   8888b.       888Y88888P888  8888b.  88888888 88888888  .d88b.";
    cout << endl << "\t8888888P\"  888  888 888 \"88b     \"88b      888 Y888P 888     \"88b    d88P     d88P  d88\"\"88b";
    cout << endl << "\t888 T88b   888  888 888  888 .d888888      888  Y8P  888 .d888888   d88P     d88P   888  888";
    cout << endl << "\t888  T88b  Y88b 888 888 d88P 888  888      888   \"   888 888  888  d88P     d88P    Y88..88P";
    cout << endl << "\t888   T88b  \"Y88888 88888P\"  \"Y888888      888       888 \"Y888888 88888888 88888888  \"Y88P\"\n";
    textcolor(BROWN);
    cout << endl << "\t\t\tGioco sviluppato da Verma Abhijeet e Catellani Filippo \n";
    textcolor(WHITE);
    if(num == 1){
        cout << endl << "\t\t\t\t\tGiocatore vs Giocatore";
    } else if (num == 2){
        cout << endl << "\t\t\t\t\tGiocatore vs Computer";
    }

}


void RubaMazzo::viewRegolamento()
{
    system("cls");
    title(-1);
    cout << endl << endl << "Di seguito e' riportato il regolamento del gioco Rubamazzo: " << endl << endl;
    cout << endl << "--------------------------------------------------------------------------------------";
    cout << endl << " - Rubamazzo si gioca in due (Giocatore 1 vs Giocatore 2 oppure Giocatore vs computer).";
    cout << endl << " - Si danno tre carte a ciascun giocatore, quindi mette quattro carte sul tavolo. ";
    cout << endl << " - Quando i due giocatori hanno giocato tutte le proprie carte,";
    cout << " il mazziere ne distribuisce altre tre a ciascuno: \n   questo si ripete fino ad esaurimento del mazzo." << endl << endl;

    cout << " - Ciascun giocatore a turno gioca una carta fino ad esaurimento delle carte. ";
    cout << endl << " - Se la carta giocata e' di valore uguale a quello di una carta, il giocatore prende la carta da lui giocata";
    cout << endl << "   e quella di valore corrispondente, e le pone in un mazzetto di fronte a se'";
    cout << endl << "   con la faccia rivolta verso l'alto.";
    cout << endl << " - E' possibile inoltre rubare il mazzo avversario se si gioca una carta il cui valore corrisponde a";
    cout << endl << "   quello della carta disposta a faccia in su del mazzetto avversario." << endl << endl;

    textbackground(BROWN);
    textcolor(BLACK);
    cout << endl << endl << "--------------------------------------------------------------------------------------";
    cout << endl << "- Vince la partita il giocatore che ha un numero maggiore di carte nel proprio mazzo. ";
    cout << endl << "--------------------------------------------------------------------------------------";
    textbackground(BLACK);
    textcolor(WHITE);
    cout << endl << endl;
    system("pause");

}
