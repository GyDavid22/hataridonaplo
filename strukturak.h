#ifndef STRUKTURAK_H_INCLUDED
#define STRUKTURAK_H_INCLUDED

typedef struct datum
{
    int ev;
    int ho;
    int nap;
    int ora;
    int perc;
} datum;

typedef struct esemeny
{
    char *nev;
    char *leiras;
    char *hely;
    datum idopont;
} esemeny;

typedef struct dinint
{
    int *tomb;
    int meret;
    int *datediff;
} dinint;

typedef struct lancint
{
    int szam;
    struct lancint *kov; /* láncolt lista */
} lancint;

#endif // STRUKTURAK_H_INCLUDED
