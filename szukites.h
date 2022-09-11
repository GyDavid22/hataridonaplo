#ifndef SZUKITES_H_INCLUDED
#define SZUKITES_H_INCLUDED

#include "strukturak.h"

dinint *szukites(esemeny **adatbazis, int *elemszam);
void listazas(esemeny **adatbazis, dinint *listazando);
void rendez(dinint **lista);

#endif // SZUKITES_H_INCLUDED
