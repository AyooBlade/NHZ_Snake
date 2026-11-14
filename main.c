#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "megjelenites.h"
#include "jatek.h"
#include "debugmalloc.h"

static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo, Etel *etel);


int main(int argc, char *argv[]) {
    Etel etel;
    Game game = {
        .window = NULL,
        .renderer = NULL,
    };
    Kigyo kigyo = {
        .irany = LE,
        .pont = 0,
        .el = true,
    };

    //csekkoljuk hogy az SDL nem e futott hibára
    if (initSDL(&game)) {
        cleanup(&game, EXIT_FAILURE);
        exit(1);
    }

    unsigned int lastTime = 0, currentTime;

    //Jatek
    while (true) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            esemeny_kezeles(&game, &event, &kigyo, &etel);
        }

                                                                                                    //kígyó mozgatása
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + KIGYO_SPEED) {
            kigyo_fej_lep(&kigyo);
            //printf("etel: %d, %d | fej: %d, %d\n", etel.x, etel.y,kigyo.fej.x, kigyo.fej.y);
            if (kigyo.pont> 0) {
                kigyo_test_lep(&kigyo);
            }
            lastTime = currentTime;
        }
        if (!etel.van_e) {                                                                         //megnézzük van e már letéve étel ha nem letesszük.
            etel_spawn(&kigyo, &etel);
            etel.van_e = true;
        }

        bool felvette = etel_felszedes(&kigyo, &etel);                                              //felvette a kigyó az ételt vizsgálása
        if (felvette) {
            etel.van_e = false;
            felvette = false;
            kigyo_novekedes(&kigyo);
            kigyo.pont += 1;

        }


        SDL_RenderClear(game.renderer);


        kigyo_fej_kirajz(&kigyo, &game);                                                           //kigyó feje kirajzolása
        kigyo_test_kirajz(&kigyo, &game);                                                           //kigyó teste kirajzolása

        etel_kirajz(&game, &etel);

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderPresent(game.renderer);   //frissiti a kepernyot

        SDL_Delay(16);                          //60fps-es loop: 16ms
    }
    cleanup(&game, EXIT_SUCCESS);
    return 0;
}


//gombok, események kezelése, hogy mi történjen melyik gombra
static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo, Etel *etel) {
    switch (event->type) {
        case SDL_QUIT:
            clear_jatek(kigyo);
            cleanup(game, EXIT_SUCCESS);
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {                                             //iranyitas
                case SDLK_w:
                    kigyo->irany = kigyo->irany == LE ? LE : FEL;                              //Ha lefele megy ne tudjon felfele menni -> 180 fokos fordulatokat kizárjuk
                    // kigyo->irany = FEL;
                    break;
                case SDLK_s:
                    kigyo->irany = kigyo->irany == FEL ? FEL : LE;
                    // kigyo->irany = LE;
                    break;
                case SDLK_a:
                    kigyo->irany = kigyo->irany == JOBBRA ? JOBBRA : BALRA;
                    //kigyo->irany = BALRA;
                    break;
                case SDLK_d:
                    kigyo->irany = kigyo->irany == BALRA ? BALRA : JOBBRA;
                    //kigyo->irany = JOBBRA;
                    break;
                case SDLK_q:                                                            //pont hozzáadás
                    kigyo->pont += 1;
                    etel->van_e = false;
                    kigyo_novekedes(kigyo);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}





