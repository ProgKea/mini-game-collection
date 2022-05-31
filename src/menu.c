#include "menu.h"

#define MENU_COUNT 2

const SDL_Color SEL_COLOR = {94, 172, 211};
const SDL_Color WHITE = {255, 255, 255};
const SDL_Color BG_COLOR = {28, 28, 28};

typedef struct SDL_Font {
  SDL_Rect rect[MENU_COUNT];
  SDL_Surface *surface[MENU_COUNT];
  SDL_Texture *texture[MENU_COUNT];
  int tex_w[MENU_COUNT];
  int tex_h[MENU_COUNT];
  TTF_Font *font;
} SDL_Font;

/* MENU */
bool is_menu = true;
SDL_Font menu_items;
const char *menu_text[MENU_COUNT];
int item_index;

void load_text(SDL_Renderer *renderer, int screen_width) {
  for (int i = 0; i < MENU_COUNT; i++) {
    if (i == item_index)
      menu_items.surface[i] =
          TTF_RenderText_Solid(menu_items.font, menu_text[i], SEL_COLOR);
    else
      menu_items.surface[i] =
          TTF_RenderText_Solid(menu_items.font, menu_text[i], WHITE);

    menu_items.texture[i] =
        SDL_CreateTextureFromSurface(renderer, menu_items.surface[i]);

    SDL_QueryTexture(menu_items.texture[i], NULL, NULL, &menu_items.tex_w[i],
                     &menu_items.tex_h[i]);

    menu_items.rect[i].w = menu_items.tex_w[i];
    menu_items.rect[i].h = menu_items.tex_h[i];
    menu_items.rect[i].x = screen_width / 2 - menu_items.rect[i].w / 2;
  }
}

void init_menu_items(SDL_Renderer *renderer, int screen_width) {
  menu_text[0] = "Flappy Bird";
  menu_text[1] = "Pong";
  item_index = 0;
  menu_items.font = TTF_OpenFont("Roboto.ttf", 64);
  load_text(renderer, screen_width);
}

void render_text(SDL_Renderer *renderer, int x, int start_y, int gapy) {
  int y = start_y;

  for (int i = 0; i < MENU_COUNT; i++) {
    menu_items.rect[i].y = y;
    SDL_RenderCopy(renderer, menu_items.texture[i], NULL, &menu_items.rect[i]);
    y += gapy;
  }
}

void destroy_text() {
  for (int i = 0; i < MENU_COUNT; i++) {
    SDL_DestroyTexture(menu_items.texture[i]);
    SDL_FreeSurface(menu_items.surface[i]);
    TTF_CloseFont(menu_items.font);
  }
}

void menu_keys(SDL_Keycode key) {
  SDL_Log("You pressed something\n");
}

void render_menu(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  render_text(renderer, 100, 100, 100);
  SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b,
                         BG_COLOR.a);
  SDL_RenderPresent(renderer);
}
