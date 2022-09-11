#include <stdio.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "db_kezeles.h"
#include "esemeny_felvesz.h"
#include "strukturak.h"

/* adatbázis létrehozása, illetve fájlból adatok beolvasása */
void inicializalas (esemeny **adatbazis, int *elemszam)
{
    FILE *fp;
    fp = fopen("db.txt", "rt");
    if (fp != NULL) /* akkor olvasunk be, ha a fájl létezik */
    {
        printf("Az adatbazis betoltese folyamatban...");
        fscanf(fp, "%d", elemszam);
        while(fgetc(fp) != '\n');
        *adatbazis = (esemeny*) malloc(sizeof(esemeny) * (*elemszam));
        for (int i = 0; i < *elemszam; ++i)
        {
            ((*adatbazis)+i)->nev = szoveg_beolvas(fp);
            ((*adatbazis)+i)->leiras = szoveg_beolvas(fp);
            ((*adatbazis)+i)->hely = szoveg_beolvas(fp);
            fscanf(fp, "%d.%d.%d. %d:%d\n", &((*adatbazis)+i)->idopont.ev, &((*adatbazis)+i)->idopont.ho, &((*adatbazis)+i)->idopont.nap, &((*adatbazis)+i)->idopont.ora, &((*adatbazis)+i)->idopont.perc);
        }
        fclose(fp);
    }
    else /* ha nincs fájl, létrehozzuk a kiindulási állapotot */
    {
        *adatbazis = (esemeny*) malloc(sizeof(esemeny));
        *elemszam = 0;
    }
}

void tomb_atmeretez(esemeny **adatbazis, int *meret, bool novel)
{
    if (novel)
    {
        *adatbazis = (esemeny*) realloc(*adatbazis, sizeof(esemeny)*(++*meret));
    }
    else
    {
        *adatbazis = (esemeny*) realloc(*adatbazis, sizeof(esemeny)*(--*meret));
    }
}

void mentes (esemeny **adatbazis, int *elemszam)
{
    FILE *fp;
    fp = fopen("db.txt", "wt");
    fprintf(fp, "%d\n", *elemszam);
    for (int i = 0; i < *elemszam; ++i)
    {
        fprintf(fp, "%s\n", ((*adatbazis) + i)->nev);
        fprintf(fp, "%s\n", ((*adatbazis) + i)->leiras);
        fprintf(fp, "%s\n", ((*adatbazis) + i)->hely);
        fprintf(fp, "%d.%02d.%02d. %d:%02d\n", ((*adatbazis) + i)->idopont.ev, ((*adatbazis) + i)->idopont.ho, ((*adatbazis) + i)->idopont.nap, ((*adatbazis) + i)->idopont.ora, ((*adatbazis) + i)->idopont.perc);
    }
    fclose(fp);
}
