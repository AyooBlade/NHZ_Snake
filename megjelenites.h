//
// Created by akosr on 08/11/2026.
//

#ifndef NHZ_SNAKE_MEGJELENITES_H
#define NHZ_SNAKE_MEGJELENITES_H




typedef struct Game{
    SDL_Window *window;
    SDL_Renderer *renderer;
}Game;

#define WINDOW_TITLE "The Snake Game"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


bool initSDL(Game *game);
void cleanup(Game *game, int exit_status);

#endif //NHZ_SNAKE_MEGJELENITES_H