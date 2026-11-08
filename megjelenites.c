//
// Created by akosr on 08/11/2026.
//
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdbool.h>
#include "megjelenites.h"


//töröljük a memóriából az sdl-es dolgokat.
void cleanup(Game *game, int exit_status) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(exit_status);
}
//inicializáljuk az sdl-t True-t ad vissza ha hiba történik
bool initSDL(Game *game) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {                                                //SDL inicializiasa összes flag-gel.
        fprintf(stderr, "Nem sikerult inicaializalni az SDL: %s\n", SDL_GetError());
        return true;
    }
    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT,0);    //létrehozzuk az ablakot.
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