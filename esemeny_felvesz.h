#ifndef ESEMENY_FELVESZ_H_INCLUDED
#define ESEMENY_FELVESZ_H_INCLUDED

#include "strukturak.h"

void esemenyt_felvesz (esemeny **adatbazis, int *elemszam);
char *szoveg_beolvas(FILE *bemenet);
bool datum_ellenorzes(datum *datum);

typedef struct lanclist {

    char betu;
    struct lanclist *kov;

} lanclist;

#endif // ESEMENY_FELVESZ_H_INCLUDED
