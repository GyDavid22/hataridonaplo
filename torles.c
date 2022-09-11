#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "debugmalloc.h"
#include "torles.h"
#include "strukturak.h"
#include "szukites.h"
#include "db_kezeles.h"

void esemenyt_torol(esemeny **adatbazis, int *meret)
{
    dinint *listazando = szukites(&*adatbazis, meret);
    listazas(&*adatbazis, listazando);
    if (listazando->meret != 0)
    {
        printf("Kerem, irja be a torlendo esemeny melletti szamot! ");
        int torlendo = -1;
        while (torlendo == -1)
        {
            scanf("%d", &torlendo);
            while (getchar() != '\n');
            if (torlendo < 1 || torlendo > listazando->meret)
            {
                printf("A kivalasztott szam nem megfelelo!\n");
                torlendo = -1;
            }
        }
        unsigned char megerosites;
        unsigned char temp;
        bool megfelel = false;
        while(!megfelel)
        {
            printf("Biztos, hogy torolni szeretne a kivalasztott esemenyt? (I/N) ");
            while((temp = getchar()) != '\n')
            {
                megerosites = temp;
            }
            switch(tolower(megerosites))
            {
            case 'i':
                megfelel = true;
                break;
            case 'n':
                return;
            default:
                printf("Ez a valasztas nem megfelelo!\n");
                break;
            }
        }
        torlendo = *(listazando->tomb + (torlendo - 1));
        free(((*adatbazis) + torlendo)->nev);
        free(((*adatbazis) + torlendo)->leiras);
        free(((*adatbazis) + torlendo)->hely);
        for (int i = torlendo + 1; i < *meret; ++i) /* túlindexelés elkerülése */
        {
            ((*adatbazis)+i-1)->nev = ((*adatbazis)+i)->nev;
            ((*adatbazis)+i-1)->leiras = ((*adatbazis)+i)->leiras;
            ((*adatbazis)+i-1)->hely = ((*adatbazis)+i)->hely;
            ((*adatbazis)+i-1)->idopont = ((*adatbazis)+i)->idopont;
        }
        tomb_atmeretez(&*adatbazis, meret, false);
        mentes(&*adatbazis, meret);
    }
    else
    {
        while(getchar() != '\n');
    }
    free(listazando->datediff);
    free(listazando->tomb);
    free(listazando);
}
