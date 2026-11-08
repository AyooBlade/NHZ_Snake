//
// Created by akosr on 08/11/2026.
//

#include "jatek.h"

#include <stdio.h>

void kigyo_fej_lep(Kigyo *kigyo) {
    switch (kigyo->irany) {
        case FEL:
            kigyo->fej.y +=1;
            break;
        case LE:
            kigyo->fej.y -=1;
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
    printf("%d, %d ; irany: %d | ", kigyo->fej.x, kigyo->fej.y, kigyo->irany);
}

