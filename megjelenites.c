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

void kigyo_fej_kirajz(Kigyo *kigyo, Game *game) {
    int fejx = kigyo->fej.x*50;
    int fejy = kigyo->fej.y*50;

    SDL_Rect negyzet = {fejx,fejy,50,50};                   //negyzet parameterei
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);     //negyzet színe
    SDL_RenderFillRect(game->renderer, &negyzet);                       //negyzet kitöltése
    SDL_RenderDrawRect(game->renderer, &negyzet);                       //negyzet kirajzolása

}
void kigyo_test_kirajz(Kigyo *kigyo, Game *game) {
    Szegmens *current = kigyo->fej.kovetkezo;

    while (current != NULL) {
        int test_x = current->x*50;
        int test_y = current->y*50;
        SDL_Rect negyzet = {test_x,test_y,50,50};
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(game->renderer, &negyzet);
        SDL_RenderDrawRect(game->renderer, &negyzet);
        current = current->kovetkezo;
    }

}
