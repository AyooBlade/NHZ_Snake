#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "megjelenites.h"
#include "jatek.h"


static void esemeny_kezeles(Game *game, SDL_Event *event);


int main(int argc, char *argv[]) {
    Game game = {
        .window = NULL,
        .renderer = NULL,
    };

    if (initSDL(&game)) {
        cleanup(&game, EXIT_FAILURE);
        exit(1);
    }
   bool gameGoing=true;
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            esemeny_kezeles(&game, &event);
        }

        SDL_RenderClear(game.renderer);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);                          //60fps-es loop
    }
    cleanup(&game, EXIT_SUCCESS);
    return 0;
}


//gombok, események kezelése, hogy mi történjen melyik gombra
static void esemeny_kezeles(Game *game, SDL_Event *event) {
    switch (event->type) {
        case SDL_QUIT:
            cleanup(game, EXIT_SUCCESS);
            break;
        default:
            break;
    }
}





