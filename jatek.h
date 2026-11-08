//
// Created by akosr on 08/11/2026.
//

#include <stdbool.h>

#ifndef NHZ_SNAKE_JATEK_H
#define NHZ_SNAKE_JATEK_H

#endif //NHZ_SNAKE_JATEK_H

#define KIGYO_SPEED 150


typedef enum Irany{FEL,LE,BALRA,JOBBRA} Irany;

typedef struct Szegmens {
    int x,y;
    struct Szegmens *kovetkezo;
}Szegmens;

typedef struct Kigyo {
    Irany irany;
    Szegmens fej;
    int pont;
    bool el;
}Kigyo;

typedef struct Jatek_m {
    Kigyo kigyo[2];
    int kigyok_szama;
};


void kigyo_fej_lep(Kigyo *kigyo);

void kigyo_test_lep(Kigyo *kigyo);
