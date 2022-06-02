#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "flappybird.h"
#include "game_state.h"

#define FONT_PATH "assets/fonts/iosevka.ttf"
#define MENU_COUNT 2
#define FONT_SIZE 100

typedef struct MenuItems {
  SDL_Rect rect[MENU_COUNT];
  SDL_Surface *surface[MENU_COUNT];
  SDL_Texture *texture[MENU_COUNT];
  int tex_w[MENU_COUNT];
  int tex_h[MENU_COUNT];
  const char *text[MENU_COUNT];
  unsigned int index;
  TTF_Font *font;
  Mix_Chunk *menu_sound;
  Mix_Chunk *enter_sound;
} MenuItems;

MenuItems create_menu(SDL_Renderer *renderer, int screen_width);

void render_menu(SDL_Renderer *renderer, MenuItems *menu_items);
void menu_events(SDL_Event e, SDL_Renderer *renderer, MenuItems *menu_items,
                 int screen_width);
void destroy_menu(MenuItems menu_items);
#endif
