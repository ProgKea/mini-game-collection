#include "menu.h"

#define MENU_COUNT 3
#define FONT_SIZE 100

const SDL_Color SEL_COLOR = {94, 172, 211};
const SDL_Color WHITE = {255, 255, 255};
const SDL_Color BG_COLOR = {28, 28, 28};

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

/* MENU */
bool is_menu = true;
SDL_Font menu_items;

void load_text(SDL_Renderer *renderer, int screen_width) {
  for (int i = 0; i < MENU_COUNT; i++) {
    if (i == menu_items.index)
      menu_items.surface[i] =
          TTF_RenderText_Solid(menu_items.font, menu_items.text[i], SEL_COLOR);
    else
      menu_items.surface[i] =
          TTF_RenderText_Solid(menu_items.font, menu_items.text[i], WHITE);

    menu_items.texture[i] =
        SDL_CreateTextureFromSurface(renderer, menu_items.surface[i]);

    SDL_QueryTexture(menu_items.texture[i], NULL, NULL, &menu_items.tex_w[i],
                     &menu_items.tex_h[i]);

    SDL_FreeSurface(menu_items.surface[i]);

    menu_items.rect[i].w = menu_items.tex_w[i];
    menu_items.rect[i].h = menu_items.tex_h[i];
    menu_items.rect[i].x = screen_width / 2 - menu_items.rect[i].w / 2;
  }
}

void init_menu_items(SDL_Renderer *renderer, int screen_width) {
  menu_items.text[0] = "Flappy Bird";
  menu_items.text[1] = "Pong";
  menu_items.text[2] = "Tetris";
  menu_items.index = 0;
  menu_items.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  TTF_SetFontHinting(menu_items.font, TTF_HINTING_LIGHT_SUBPIXEL);
  if (menu_items.font == NULL) {
    fprintf(stderr, "Failed to open font: %s\n", SDL_GetError());
  }

  load_text(renderer, screen_width);
}

void render_text(SDL_Renderer *renderer, int start_y, int gapy) {
  int y = start_y;

  for (int i = 0; i < MENU_COUNT; i++) {
    menu_items.rect[i].y = y;
    SDL_RenderCopy(renderer, menu_items.texture[i], NULL, &menu_items.rect[i]);
    y += gapy;
  }
}

void destroy_menu() {
  if (menu_items.font == NULL) {
    TTF_CloseFont(menu_items.font);
  }

  for (int i = 0; i < MENU_COUNT; i++) {
    SDL_DestroyTexture(menu_items.texture[i]);
  }
}

void menu_item_up(SDL_Renderer *renderer, int screen_width) {
  if (menu_items.index > 0) {
    menu_items.index--;
    load_text(renderer, screen_width);
  }
}

void menu_item_down(SDL_Renderer *renderer, int screen_width) {
  if (menu_items.index < MENU_COUNT - 1) {
    menu_items.index++;
    load_text(renderer, screen_width);
  }
}

void menu_events(SDL_Event e, SDL_Renderer *renderer, int screen_width) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      menu_item_up(renderer, screen_width);
      break;
    case SDLK_DOWN:
      menu_item_down(renderer, screen_width);
      break;
    }
  }
}

void render_menu(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  render_text(renderer, 100, FONT_SIZE * 1.56);
  SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b,
                         BG_COLOR.a);
  SDL_RenderPresent(renderer);
}
