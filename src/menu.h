#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define FONT_PATH "assets/fonts/iosevka.ttf"
#define MENU_COUNT 3
#define FONT_SIZE 100

typedef struct SDL_Font {
  SDL_Rect rect[MENU_COUNT];
  SDL_Surface *surface[MENU_COUNT];
  SDL_Texture *texture[MENU_COUNT];
  int tex_w[MENU_COUNT];
  int tex_h[MENU_COUNT];
  const char *text[MENU_COUNT];
  unsigned int index;
  TTF_Font *font;
} SDL_Font;

SDL_Font create_menu(SDL_Renderer *renderer, int screen_width);

void render_menu(SDL_Renderer *renderer, SDL_Font *menu_items);
void menu_events(SDL_Event e, SDL_Renderer *renderer, SDL_Font *menu_items,
                 int screen_width);
void destroy_menu(SDL_Font menu_items);

extern bool is_menu;

#endif
