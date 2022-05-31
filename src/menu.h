#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define FONT_PATH "assets/fonts/iosevka.ttf"

void render_menu(SDL_Renderer *renderer);
void menu_events(SDL_Event e, SDL_Renderer *renderer, int screen_width);
void init_menu_items(SDL_Renderer *renderer, int screen_width);
void destroy_menu();

extern bool is_menu;

#endif
