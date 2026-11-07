#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>

typedef struct Game{
    SDL_Window *window;
    SDL_Renderer *renderer;
}Game;


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool initSDL();
void cleanup();


int main(int argc, char *argv[]) {
    Game game = {
        .window = NULL,
        .renderer = NULL,
    };

    if (initSDL(&game)) {
        cleanup(&game);
        exit(1);
    }

    SDL_RenderClear(game.renderer);

    SDL_RenderPresent(game.renderer);

    SDL_Delay(5000);

    cleanup(&game);
    exit(0);
    return 0;
}




void cleanup(Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

bool initSDL(Game *game) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {                                                //SDL inicializiasa összes flag-gel.
        fprintf(stderr, "Nem sikerult inicaializalni az SDL: %s\n", SDL_GetError());
        return true;
    }
    game->window = SDL_CreateWindow("The Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT,0);    //létrehozzuk az ablakot.
    if (!game->window) {
        fprintf(stderr, "Nem sikerult megcsinalni az ablakot: %s\n", SDL_GetError());
        return true;
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);                           //létrehozzuk a renderer-t.
    if (!game->renderer) {
        fprintf(stderr, "Nem sikerult a renderer: %s\n", SDL_GetError());
        return true;
    }


    return false;
}


