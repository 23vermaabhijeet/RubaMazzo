#ifndef RUBAMAZZO_H
#define RUBAMAZZO_H

#include "napoletano.h"


class RubaMazzo : public Napoletano{

public:
    RubaMazzo();
    ~RubaMazzo();

    void initialize(); // metodo abilitato all'inizializzazione del mazzo di 40 carte (metodo che simula il mescolamento del mazzo)
    void startGame(); // metodo utilizzato per iniziare una partita
    void giocatore(int* &mano, int* &mazzo, int numMano, int numMazzo); // metodo che fornisce l'interfaccia che permette ad un
    // giocatore di interagire con il sistema (per esempio selezionare quale carta mettere al centro del tavolo

    void computer(); // metodo utilizzato per eseguire ilm turno di gioco del computer
    void giocatoreVsComputer(); // metodo che permette di iniziare e svolgere una partita Giocatore vs Computer
    void giocatoreVsGiocatore(); // metodo che permette di iniziare e svolgere una partita Giocatore vs Giocatore
    int removeElem(int* &mazzo, int numMazzo, int pos); // metodo utilizzato per rimuovere una carta dal mazzo
    void add(int* &mazzo, int numMazzo, int elem); // metodo utilizzato per aggiungere una carta ad un mazzo
    void print(int* &mazzo, int numMazzo); // metodo utilizzato per stampare le carte di un mazzo

    void ricarica(); // metodo che simula la ridistribuzione di tre carte per giocatore quando entrambi hanno terminato le carte
    //presenti nella loro mano

    void printMazzi(int numMazzo); // metodo utilizzato per stampare i mazzi numero 1, 2, 3
    bool removeCentroAddinMazzo(int* &mano, int* &mazzo, int numMano, int numMazzo, int pos, int* &mazzoPart, int numMazzoPart); // metodo
    // utilizzato per rimuovere una carta dal mazzo 1 (ossia le carte presenti al centro) ed aggiungerlo nel mazzo personale di un giocatore

    void title(int num); // metodo abilitato alla stampa dell'ASCII ART che raffigura il nome del gioco

    bool rubaMazzo(int* &mazzo, int numMazzo, int scelta, int* &mazzoDest, int numDest); // metodo che permette ad un giocatore di rubare
    // il mazzo avversario quando c'è la possibilità di effettuare tale azione


    void tryFindCarta(); // metodo utilizzato quando si è deciso di giocare alla modalità GIOCATORE vs COMPUTER, tale metodo permette al computer di
    // andare a confrontare tutte le carte della sua mano con le carte presenti nel tavolo, per cercare una possibile carta da prendere ed aggiungere
    // al suo mazzo, se invece non c'è alcuna carta che si può prendere andrà a mettere una carta sua della mano nel centro

protected:
    int *carteMazzo; // 0   mazzo integrale che all'inizio del gioco ha 40 carte
    int *centro; // 1   insieme di carte presenti sul tavolo
    int *mazzoG1; // 2   insieme di carte raccolte nel corso del gioco dal giocatore 1
    int *mazzoG2; // 3   insieme di carte raccolte nel corso del gioco dal giocatore 2
    int *manoG1; // 4   insieme di carte presenti nella mano del giocatore 1
    int *manoG2; // 5   Giocatore o computer - insieme di carte presenti nella mano del giocatore 2
    int *dim;

private:
    int typeGame(); // metodo che permette di andare a selezionare quale modalità si vuole giocare
    bool isPresent(int elem, int* mazzo, int dim); // metodo che restituisce true se la carta elem è presente in un mazzo altrimenti false
    int searchCentro(int elem); // metodo di ricerca lineare che restituisce -1 se la carta non è stata trovata nel centro, altrimenti restituisce
    //la posizione della carta elem nelle carte del centro
    void viewRegolamento(); // metodo che permette di visualizzare il regolamento del gioco;
};


#endif //RUBAMAZZO_H
