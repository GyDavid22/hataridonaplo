#include <stdio.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "kiiras.h"
#include "strukturak.h"
#include "szukites.h"

void kiir(esemeny **adatbazis, int *meret)
{
    dinint *listazando = szukites(&*adatbazis, meret);
    if (listazando->meret == 0)
    {
        printf(" - nincs a keresesnek megfelelo elem -\n");
    }
    else
    {
        for (int i = 0; i < listazando->meret; ++i)
        {
            printf("\n%d./%d.: ", i+1, listazando->meret);
            int kulonb = *(listazando->datediff + i);
            if (kulonb < 0)
            {
                printf("(%d nappal ezelott)", kulonb*(-1));
            }
            else if (kulonb > 0)
            {
                printf("(%d nap mulva)", kulonb);
            }
            else
            {
                printf("(Ma van)");
            }
            printf("\n");
            printf("Nev: %s\n", ((*adatbazis) + *(listazando->tomb + i))->nev);
            printf("Leiras: %s\n", ((*adatbazis) + *(listazando->tomb + i))->leiras);
            printf("Helyszin: %s\n", ((*adatbazis) + *(listazando->tomb + i))->hely);
            printf("Idopont: %d.%02d.%02d. %d:%02d\n", ((*adatbazis) + *(listazando->tomb + i))->idopont.ev, ((*adatbazis) + *(listazando->tomb + i))->idopont.ho, ((*adatbazis) + *(listazando->tomb + i))->idopont.nap, ((*adatbazis) + *(listazando->tomb + i))->idopont.ora, ((*adatbazis) + *(listazando->tomb + i))->idopont.perc);
        }
    }
    printf("\nA menube valo visszalepeshez nyomjon meg egy gombot!");
    while(getchar() != '\n');
    free(listazando->datediff);
    free(listazando->tomb);
    free(listazando);
}
