#ifndef RUBAMAZZO_H
#define RUBAMAZZO_H

#include "napoletano.h"


class RubaMazzo : public Napoletano{

public:
    RubaMazzo();
    ~RubaMazzo();
    void initialize();
    void startGame();
    void giocatore();
    void computer();
    void giocatoreVsComputer();
    void giocatoreVsGiocatore();
    int removeElem(int* mazzo, int numMazzo);
    void add(int* mazzo, int numMazzo, int elem);
    void print(int *mazzo, int numMazzo);

    void inizio();
    void ricarica();
    void printMazzi();
    void tentativo(int* mazzo, int numMazzo, int elem);
    void removeCentroAddinMazzo(int *mazzo, int numMazzo, int pos);


protected:
    int *carteMazzo; // 0   mazzo integrale che all'inizio del gioco ha 40 carte
    int *centro; // 1   insieme di carte presenti sul tavolo
    int *mazzoG1; // 2   insieme di carte raccolte nel corso del gioco dal giocatore 1
    int *mazzoG2; // 3   insieme di carte raccolte nel corso del gioco dal giocatore 2
    int *manoG1; // 4   insieme di carte presenti nella mano del giocatore 1
    int *manoG2; // 5   insieme di carte presenti nella mano del giocatore 2
    int *dim;

private:
    int typeGame();
    bool isPresent(int elem, int* mazzo, int dim);
    int searchCentro(int elem);
};


#endif //RUBAMAZZO_H
