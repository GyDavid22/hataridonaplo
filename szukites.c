#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "debugmalloc.h"
#include "strukturak.h"
#include "esemeny_felvesz.h"
#include "dat_kulonb.h"
#include "szukites.h"

/* majd egy, az indexeket tartalmazó dinamikus tömbbel tér vissza */
dinint *szukites(esemeny **adatbazis, int *elemszam)
{
    dinint *talalatok = (dinint*) malloc(sizeof(dinint));
    time_t most = time(0);
    datum ma = { localtime(&most)->tm_year + 1900, localtime(&most)->tm_mon + 1, localtime(&most)->tm_mday };
    printf("Mi alapjan szeretne keresni?\n"
           " 1) Nev\n"
           " 2) Idopont (csak ev)\n"
           " 3) Idopont (ev es honap)\n"
           " 4) Minden kilistazasa\n");
    char input = -1;
    char temp;
    /* innentől a while ciklusig olyan dolgok vannak, amit több opció is használ, ezért vannak itt létrehozva */
    datum input2 =  { 0, 0, 1, 0, 0 }; /* megfelelő előzetes feltöltés, hogy a dátum helyességet ellenőrző programrész ne akadjon ki */
    lancint *elso = (lancint*) malloc(sizeof(lancint));
    elso->szam = -1;
    elso->kov = NULL;
    lancint *mozgo = elso;
    lancint *temp2;
    talalatok->meret = 0;
    int index = 0;
    bool eveshonap = false;
    while (input == -1)
    {
        while ((temp = getchar()) != '\n')
        {
            input = temp;
        }
        switch (input)
        {
        case '1':
            printf("Kerem, adja meg a keresendo kifejezest! (Kis- es nagybetu erzekeny!) ");
            char *keresendo = szoveg_beolvas(stdin);
            for (int i = 0; i < *elemszam; ++i)
            {
                if(strstr(((*adatbazis) + i)->nev, keresendo) != NULL)
                {
                    mozgo->szam = i;
                    mozgo->kov = (lancint*) malloc(sizeof(lancint));
                    mozgo = mozgo->kov;
                    mozgo->szam = -1;
                    mozgo->kov = NULL;
                    ++(talalatok->meret);
                }
            }
            talalatok->tomb = malloc(sizeof(int) * (talalatok->meret));
            talalatok->datediff = malloc(sizeof(int) * (talalatok->meret));
            mozgo = elso;
            while(mozgo != NULL)
            {
                if (mozgo->szam != -1)
                {
                    *(talalatok->tomb + index) = mozgo->szam;
                    *(talalatok->datediff + (index++)) = dat_kulonbseg_szamol(&ma, &((*adatbazis) + mozgo->szam)->idopont);
                }
                temp2 = mozgo->kov;
                free(mozgo);
                mozgo = temp2;
            }
            free(keresendo);
            rendez(&talalatok);
            return talalatok;
            break;
        case '2':
            eveshonap = true;
            printf("Kerem, adja meg az evet! ");
            scanf("%d", &input2.ev);
            while(getchar() != '\n');
        case '3':
            eveshonap = !eveshonap; /* nem a legszebb, de mivel 99%-ban azonos a kód a 2-es menüponttal, ezért egyesítettem őket, így sikerült */
            if (eveshonap)
            {
                do
                {
                    printf("Kerem, adja meg az evet es a honapot! (EEEE.HH) ");
                    scanf("%d.%d", &input2.ev, &input2.ho);
                    while(getchar() != '\n');
                }
                while(!datum_ellenorzes(&input2));
            }
            for (int i = 0; i < *elemszam; ++i)
            {
                if(((*adatbazis) + i)->idopont.ev == input2.ev && ((!eveshonap) || ((*adatbazis) + i)->idopont.ho == input2.ho))
                {
                    mozgo->szam = i;
                    mozgo->kov = (lancint*) malloc(sizeof(lancint));
                    mozgo = mozgo->kov;
                    mozgo->szam = -1;
                    mozgo->kov = NULL;
                    ++(talalatok->meret);
                }
            }
            talalatok->tomb = malloc(sizeof(int) * (talalatok->meret));
            talalatok->datediff = malloc(sizeof(int) * (talalatok->meret));
            mozgo = elso;
            while(mozgo != NULL)
            {
                if (mozgo->szam != -1)
                {
                    *(talalatok->tomb + index) = mozgo->szam;
                    *(talalatok->datediff + (index++)) = dat_kulonbseg_szamol(&ma, &((*adatbazis) + mozgo->szam)->idopont);
                }
                temp2 = mozgo->kov;
                free(mozgo);
                mozgo = temp2;
            }
            rendez(&talalatok);
            return talalatok;
            break;
        case '4':
            talalatok->meret = *elemszam;
            talalatok->tomb = (int*) malloc(sizeof(int) * (*elemszam));
            talalatok->datediff = (int*) malloc(sizeof(int) * (*elemszam));
            for (int i = 0; i < *elemszam; ++i)
            {
                *(talalatok->tomb + i) = i;
                *(talalatok->datediff + i) = dat_kulonbseg_szamol(&ma, &((*adatbazis) + i)->idopont);
            }
            rendez(&talalatok);
            free(elso);
            return talalatok;
            break;
        default:
            printf("A megadott opcio nem letezik.\n");
            input = -1;
            break;
        }
    }
}

void listazas(esemeny **adatbazis, dinint *listazando)
{
    if (listazando->meret == 0)
    {
        printf(" - nincs a keresesnek megfelelo elem -\n");
    }
    else
    {
        for (int i = 0; i < listazando->meret; ++i)
        {
            printf(" (%d) ", i+1);
            printf("%s ", ((*adatbazis) + *(listazando->tomb + i))->nev);
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
        }
    }
}

void rendez(dinint **lista)
{
    int tempdatediff;
    int temptomb;
    for (int i = 0; i < (*lista)->meret; ++i)
    {
        int legkisebb = i;
        for (int j = i + 1; j < (*lista)->meret; ++j)
        {
            if (*((*lista)->datediff + j) < *((*lista)->datediff + legkisebb))
            {
                legkisebb = j;
            }
        }
        if (legkisebb != i)
        {
            tempdatediff = *((*lista)->datediff + legkisebb);
            temptomb = *((*lista)->tomb + legkisebb);
            *((*lista)->datediff + legkisebb) = *((*lista)->datediff + i);
            *((*lista)->tomb + legkisebb) = *((*lista)->tomb + i);
            *((*lista)->datediff + i) = tempdatediff;
            *((*lista)->tomb + i) = temptomb;
        }
    }
}
