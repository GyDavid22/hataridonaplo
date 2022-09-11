#include <stdio.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "modositas.h"
#include "strukturak.h"
#include "szukites.h"
#include "esemeny_felvesz.h"
#include "db_kezeles.h"

void esemenyt_modosit(esemeny **adatbazis, int *meret)
{
    dinint *listazando = szukites(&*adatbazis, meret);
    listazas(&*adatbazis, listazando);
    if (listazando->meret != 0)
    {
        printf("Kerem, irja be a modositando esemeny melletti szamot (Megse: 0)! ");
        int modositando = -1;
        while (modositando == -1)
        {
            scanf("%d", &modositando);
            while (getchar() != '\n');
            if (modositando < 0 || modositando > listazando->meret)
            {
                printf("A kivalasztott szam nem megfelelo!\n");
                modositando = -1;
            }
        }
        if (modositando != 0)
        {
            printf("Valassza ki a modositando elemet! (Megse: 0)\n");
            printf(" 1) Cim: %s\n", ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->nev);
            printf(" 2) Leiras: %s\n", ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->leiras);
            printf(" 3) Helyszin: %s\n", ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->hely);
            printf(" 4) Idopont: %d.%02d.%02d. %d:%02d\n", ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ev, ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ho, ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.nap, ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ora, ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.perc);
            int input = -1;
            while (input == -1)
            {
                scanf("%d", &input);
                while (getchar() != '\n');
                switch (input)
                {
                case 1:
                    printf("Adja meg az uj cimet: ");
                    free(((*adatbazis) + *(listazando->tomb + (modositando - 1)))->nev);
                    ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->nev = szoveg_beolvas(stdin);
                    break;
                case 2:
                    printf("Adja meg az uj leirast: ");
                    free(((*adatbazis) + *(listazando->tomb + (modositando - 1)))->leiras);
                    ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->leiras = szoveg_beolvas(stdin);
                    break;
                case 3:
                    printf("Adja meg az uj helyszint: ");
                    free(((*adatbazis) + *(listazando->tomb + (modositando - 1)))->hely);
                    ((*adatbazis) + *(listazando->tomb + (modositando - 1)))->hely = szoveg_beolvas(stdin);
                    break;
                case 4:
                    do
                    {
                        printf("Adja meg az uj idopontot! (EEEE.HH.NN. OO:PP) ");
                        scanf("%d.%d.%d. %d:%d", &((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ev, &((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ho, &((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.nap, &((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.ora, &((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont.perc);
                        while(getchar() != '\n');
                    }
                    while(!datum_ellenorzes(&((*adatbazis) + *(listazando->tomb + (modositando - 1)))->idopont));
                    break;
                default:
                    input = -1;
                    printf("A kivalasztott opcio nem letezik!\n");
                    break;
                }
            }
        }
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
