#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "strukturak.h"
#include "esemeny_felvesz.h"
#include "db_kezeles.h"

void esemenyt_felvesz (esemeny **adatbazis, int *elemszam)
{
    tomb_atmeretez(&*adatbazis, elemszam, true);
    printf("Adja meg az esemeny adatait!\n");
    printf("Nev: ");
    ((*adatbazis)+(*elemszam)-1)->nev = szoveg_beolvas(stdin);
    printf("Leiras: ");
    ((*adatbazis)+(*elemszam)-1)->leiras = szoveg_beolvas(stdin);
    printf("Helyszin: ");
    ((*adatbazis)+(*elemszam)-1)->hely = szoveg_beolvas(stdin);
    do
    {
        printf("Idopont: (EEEE.HH.NN. OO:PP) ");
        scanf("%d.%d.%d. %d:%d", &((*adatbazis)+(*elemszam)-1)->idopont.ev, &((*adatbazis)+(*elemszam)-1)->idopont.ho, &((*adatbazis)+(*elemszam)-1)->idopont.nap, &((*adatbazis)+(*elemszam)-1)->idopont.ora, &((*adatbazis)+(*elemszam)-1)->idopont.perc);
        while (getchar() != '\n');
    }while(!datum_ellenorzes(&((*adatbazis)+(*elemszam)-1)->idopont));
    mentes(&*adatbazis, elemszam);
}

char *szoveg_beolvas(FILE *bemenet)
{
    lanclist *elso = (lanclist*) malloc(sizeof(lanclist));
    lanclist *mozgo = elso;
    char temp;
    int i = 0;
    while ((temp = fgetc(bemenet)) != '\n')
    {
        mozgo->betu = temp;
        mozgo->kov = (lanclist*) malloc(sizeof(lanclist));
        mozgo = mozgo->kov;
        ++i;
    }
    mozgo->betu = '\0';
    mozgo->kov = NULL;
    char *szoveg = (char*) malloc(sizeof(char) * (i + 1));
    i = 0;
    mozgo = elso;
    while (mozgo != NULL)
    {
        *(szoveg + (i++)) = mozgo->betu;
        lanclist *kovetkezo = mozgo->kov;
        free(mozgo);
        mozgo = kovetkezo;
    }
    return szoveg;
}

bool datum_ellenorzes(datum *datum)
{
    int napok[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool helyes = true;
    int ho_napjai = 0;
    if (datum->ho == 2 && (datum->ev % 400 == 0 || (datum->ev % 100 != 0 && datum->ev % 4 == 0)))
    {
        ho_napjai = 29;
    }
    else if (datum->ho >= 1 && datum->ho <= 12)
    {
        ho_napjai = napok[datum->ho - 1];
    }
    if (datum->nap < 1 || datum->nap > ho_napjai || datum->ora < 0 || datum->ora > 23 || datum->perc < 0 || datum->perc > 59)
    {
        helyes = false;
    }
    if (!helyes)
    {
        printf("A megadott datum nem helyes.\n");
    }
    return helyes;
}
