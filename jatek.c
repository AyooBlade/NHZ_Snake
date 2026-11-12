//
// Created by akosr on 08/11/2026.
//

#include "jatek.h"

#include <stdio.h>
#include <stdlib.h>

static Szegmens *farok(Kigyo *kigyo);

//kígyó fejének mozgatása gombok által
void kigyo_fej_lep(Kigyo *kigyo) {
    kigyo->fej.elozo_x = kigyo->fej.x;
    kigyo->fej.elozo_y = kigyo->fej.y;

    switch (kigyo->irany) {
        case FEL:
            kigyo->fej.y -=1;
            break;
        case LE:
            kigyo->fej.y +=1;
            break;
        case BALRA:
            kigyo->fej.x -=1;
            break;
        case JOBBRA:
            kigyo->fej.x +=1;
            break;
        default:
            break;
    }
    // printf("jelenlegi | %d, %d ; irany: %d | \n", kigyo->fej.x, kigyo->fej.y, kigyo->irany);
    // printf("elozo     | %d, %d ;           | \n", kigyo->fej.elozo_x, kigyo->fej.elozo_y);
}
//lefoglal memóriát az új testrésznek és elhelyezi a kigyó végéhez
void kigyo_novekedes(Kigyo *kigyo) {
    Szegmens *utolso = farok(kigyo);

    utolso->kovetkezo = (Szegmens *)malloc(sizeof(Szegmens));                       //lefoglaljuk az uj testrensznek(szegmens) a memoriat
    if (utolso->kovetkezo == NULL) {                                                     //ha nem foglalná le a memóriát
        return;
    }
    utolso->kovetkezo->kovetkezo = NULL;                                                //Null-ozzuk itt az új faroknak a .kovetkezo pointerét mert memória szemét lehet benne.
    utolso->kovetkezo->x = utolso->elozo_x;                                             //az új testrésznek megadjuk a koordinátát hogy hova kerüljön.
    utolso->kovetkezo->y = utolso->elozo_y;
    printf("letrehozott egy testreszet | ");
}

//kigyó testrészeit léptetjük ahogy mozog a kígyó feje előre.
void kigyo_test_lep(Kigyo *kigyo) {
    Szegmens *current = & kigyo->fej;

    while (current->kovetkezo != NULL) {
        current->kovetkezo->elozo_x = current->kovetkezo->x;                //elmentjük a koordinatajat mielött frissitjük
        current->kovetkezo->elozo_y = current->kovetkezo->y;

        current->kovetkezo->x = current->elozo_x;                           //léptetjük a koordinatajat.
        current->kovetkezo->y = current->elozo_y;

        current = current->kovetkezo;


    }
    //teszt
    printf("fej: (%d, %d) | ", kigyo->fej.x, kigyo->fej.y);
    printf("2.   (%d, %d)\n", kigyo->fej.kovetkezo->x, kigyo->fej.kovetkezo->y);
}

//farok megkeresése --> utolsó szegmens megkeresése
static Szegmens *farok(Kigyo *kigyo) {
    Szegmens *current = & kigyo->fej;
    while (current->kovetkezo != NULL) {
        current = current->kovetkezo;
    }
    return current;
}


void clear_jatek(Kigyo *kigyo) {
    Szegmens *current =  kigyo->fej.kovetkezo;
    while (current != NULL) {
        Szegmens *kov = current->kovetkezo;
        free(current);
        current = kov;
    }
}
