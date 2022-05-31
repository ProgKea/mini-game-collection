#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

void render_menu(SDL_Renderer *renderer);
void menu_keys(SDL_Keycode key);
void init_menu_items(SDL_Renderer *renderer, int screen_width);

extern bool is_menu;

#endif
