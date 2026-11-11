#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "megjelenites.h"
#include "jatek.h"
#include "debugmalloc.h"

static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo);


int main(int argc, char *argv[]) {

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
            esemeny_kezeles(&game, &event, &kigyo);
        }


                                                                                                    //kígyó mozgatása
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + KIGYO_SPEED) {
            kigyo_fej_lep(&kigyo);
            if (kigyo.pont> 0) {
                kigyo_test_lep(&kigyo);
            }
            lastTime = currentTime;
        }

        SDL_RenderClear(game.renderer);


        kigyo_fej_kirajz(&kigyo, &game);
        kigyo_test_kirajz(&kigyo, &game);
        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderPresent(game.renderer);   //frissiti a kepernyot

        SDL_Delay(16);                          //60fps-es loop: 16ms
    }
    cleanup(&game, EXIT_SUCCESS);
    return 0;
}


//gombok, események kezelése, hogy mi történjen melyik gombra
static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo) {
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





