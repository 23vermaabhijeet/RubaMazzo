#ifndef RUBAMAZZO_H
#define RUBAMAZZO_H

#include "napoletano.h"


class RubaMazzo : public Napoletano{

public:
    RubaMazzo();
    ~RubaMazzo();
    void initialize();
    void startGame();
    void giocatore(int* &mano, int* &mazzo, int numMano, int numMazzo);   //aggiornato

    void computer();
    void giocatoreVsComputer();
    void giocatoreVsGiocatore();
    int removeElem(int* &mazzo, int numMazzo, int pos);   //aggiornato
    void add(int* &mazzo, int numMazzo, int elem);
    void print(int* &mazzo, int numMazzo);

    void ricarica();
    void printMazzi(int numMazzo);
    void tentativo(int* mazzo, int numMazzo, int elem);
    bool removeCentroAddinMazzo(int* &mano, int* &mazzo, int numMano, int numMazzo, int pos, int* &mazzoPart, int numMazzoPart);   //aggiornato


    void title(int num);

    bool rubaMazzo(int* &mazzo, int numMazzo, int scelta, int* &mazzoDest, int numDest);


    void tryFindCarta();
protected:
    int *carteMazzo; // 0   mazzo integrale che all'inizio del gioco ha 40 carte
    int *centro; // 1   insieme di carte presenti sul tavolo
    int *mazzoG1; // 2   insieme di carte raccolte nel corso del gioco dal giocatore 1
    int *mazzoG2; // 3   insieme di carte raccolte nel corso del gioco dal giocatore 2
    int *manoG1; // 4   insieme di carte presenti nella mano del giocatore 1
    int *manoG2; // 5   Giocatore o computer - insieme di carte presenti nella mano del giocatore 2
    int *dim;

private:
    int typeGame();
    bool isPresent(int elem, int* mazzo, int dim);
    int searchCentro(int elem);
};


#endif //RUBAMAZZO_H
