#include <stdio.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "strukturak.h"
#include "dat_kulonb.h"
#include "esemeny_felvesz.h"
#include "strukturak.h"

void dat_kulonbseg_input()
{
    datum kezdo;
    do
    {
        printf("Kerem, adja meg a kezdo datumot! (EEEE.HH.NN.) ");
        scanf("%d.%d.%d", &kezdo.ev, &kezdo.ho, &kezdo.nap);
        while(getchar() != '\n'); /* a scanf a sor vége jelet nem nyeli be magától, a következõ input kapja meg */
        kezdo.ora = 0; /* muszáj valamit megadni, különben kiakad a helyességet ellenőrző programrész */
        kezdo.perc = 0;
    }
    while(!datum_ellenorzes(&kezdo));
    datum befejezo;
    do
    {
        printf("Kerem, adja meg a befejezo datumot! (EEEE.HH.NN.) ");
        scanf("%d.%d.%d", &befejezo.ev, &befejezo.ho, &befejezo.nap);
        while(getchar() != '\n');
        befejezo.ora = 0;
        befejezo.perc = 0;
    }
    while(!datum_ellenorzes(&befejezo));
    printf("A ket datum kozott %d nap telt el.\n", dat_kulonbseg_szamol(&kezdo, &befejezo));
    printf("A visszalepeshez nyomjon meg egy gombot.");
    while (getchar() != '\n');
}

int dat_kulonbseg_szamol(datum *kezdo, datum *veg)
{
    int kulonbseg1 = 0;
    int kulonbseg2 = 0;
    int napok[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    datum etalon = { 1970, 1, 1 };
    kulonbseg1 += (kezdo->ev-etalon.ev)*365;
    for (int i = kezdo->ho-2; i >= etalon.ho-1; --i) /* azért -2, mert egyrészt a hónap számát szinkronba kell hozni a tömb számozásával, másrészt például ha a kezdõdátum januárban van, akkor január hó napjait nem kell hozzáadni a különbséghez */
    {
        if (i == 1)
        {
            if (kezdo->ev % 400 == 0 || (kezdo->ev % 100 != 0 && kezdo->ev % 4 == 0))
            {
                kulonbseg1 += 29;
            }
            else
            {
                kulonbseg1 += napok[i];
            }
        }
        else
        {
            kulonbseg1 += napok[i];
        }
    }
    kulonbseg1 += kezdo->nap-etalon.nap;
    kulonbseg2 += (veg->ev-etalon.ev)*365;
    for (int i = veg->ho-2; i >= etalon.ho-1; --i)
    {
        kulonbseg2 += napok[i];
    }
    kulonbseg2 += veg->nap-etalon.nap;
    // szökőév korrigálás
    int korrekcio = 0;
    int mini;
    int maxi;
    if (kezdo->ev < veg->ev)
    {
        mini = kezdo->ev;
        maxi = veg->ev;
    }
    else
    {
        mini = veg->ev;
        maxi = kezdo->ev;
    }
    for (int i = mini + mini % 4; i <= maxi; ++i)
    {
        if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0))
        {
            ++korrekcio;
        }
        if (i == veg->ev && veg->ho < 3 && (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0)))
        {
            --korrekcio;
        }
    }
    int vegosszeg = kulonbseg2 - kulonbseg1;
    if (vegosszeg < 0)
    {
        return vegosszeg - korrekcio + 2; /* matematikailag így tűnik helyesnek */
    }
    else
    {
        return vegosszeg + korrekcio;
    }
}
