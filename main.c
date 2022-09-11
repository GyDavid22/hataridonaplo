#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>

#include "debugmalloc.h"
#include "strukturak.h"
#include "esemeny_felvesz.h"
#include "torles.h"
#include "modositas.h"
#include "kiiras.h"
#include "db_kezeles.h"
#include "dat_kulonb.h"

int main(void)
{
    char verzio[] = "Hataridonaplo v1.2 - 2021.09.26.";
    SetConsoleTitle(verzio);
    esemeny *adatbazis;
    int db_elemszam = 0;
    inicializalas(&adatbazis, &db_elemszam);
    bool run = true;
    while (run)
    {
        system("cls");
        if (db_elemszam == 0)
        {
            printf("Nem talalhato esemeny az adatbazisban. Kerem, adja meg az elso esemenyt!\n");
            esemenyt_felvesz(&adatbazis, &db_elemszam);
            system("cls");
        }
        printf("Udvozli a hataridonaplo! Kerem, valasszon az alabbi menupontok kozul!\n"
               " 1) Esemeny felvetele\n"
               " 2) Esemeny torlese\n"
               " 3) Esemeny modositasa\n"
               " 4) Esemenyek kilistazasa\n"
               " 5) Datumok kozotti kulonbseg kiszamitasa\n"
               " 6) Nevjegy\n"
               " X) Kilepes\n");
        unsigned char input = ' ';
        char temp;
        while((temp = getchar()) != '\n')
        {
            input = temp;
        } /* ez az egész arra az esetre kell, ha az user több karaktert ír be, illetve hogy az új sor jel ne zavarjon be később */
        system("cls");
        switch (toupper(input))
        {
        case '1':
            esemenyt_felvesz(&adatbazis, &db_elemszam);
            break;
        case '2':
            esemenyt_torol(&adatbazis, &db_elemszam);
            break;
        case '3':
            esemenyt_modosit(&adatbazis, &db_elemszam);
            break;
        case '4':
            kiir(&adatbazis, &db_elemszam);
            break;
        case '5':
            dat_kulonbseg_input();
            break;
        case '6':
            printf("%s\n"
                   "Keszitette: Gyenes David Andras, 2021\n"
                   "\nA visszalepeshez nyomjon meg egy gombot!", verzio);
            while(getchar() != '\n');
            break;
        case 'X':
            run = false;
            break;
        default:
            printf("A kivalasztott menupont nem letezik!");
            while (getchar() != '\n');
            break;
        }
    }
    for (int i = 0; i < db_elemszam; ++i)
    {
        free((adatbazis + i)->nev);
        free((adatbazis + i)->leiras);
        free((adatbazis + i)->hely);
    }
    free(adatbazis);
    return 0;
}
