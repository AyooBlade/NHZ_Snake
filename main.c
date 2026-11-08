#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "megjelenites.h"
#include "jatek.h"


static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo);


int main(int argc, char *argv[]) {

    Game game = {
        .window = NULL,
        .renderer = NULL,
    };

    Kigyo kigyo = {
        .irany = FEL,
        .pont = 0,
        .el = true,
    };

    //csekkoljuk hogy az SDL nem e futott hibára
    if (initSDL(&game)) {
        cleanup(&game, EXIT_FAILURE);
        exit(1);
    }

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            esemeny_kezeles(&game, &event, &kigyo);
        }

        kigyo_fej_lep(&kigyo);
        if (kigyo.pont> 0) {
            kigyo_test_lep(&kigyo);
        }



        SDL_RenderClear(game.renderer);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(1000);                          //60fps-es loop 16ms
    }
    cleanup(&game, EXIT_SUCCESS);
    return 0;
}


//gombok, események kezelése, hogy mi történjen melyik gombra
static void esemeny_kezeles(Game *game, SDL_Event *event, Kigyo *kigyo) {
    switch (event->type) {
        case SDL_QUIT:
            cleanup(game, EXIT_SUCCESS);
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_w:
                    kigyo->irany = FEL;
                    break;
                case SDLK_s:
                    kigyo->irany = LE;
                    break;
                case SDLK_a:
                    kigyo->irany = BALRA;
                    break;
                case SDLK_d:
                    kigyo->irany = JOBBRA;
                    break;
                case SDLK_q:
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





