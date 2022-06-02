#include "menu.h"

const SDL_Color SEL_COLOR = {94, 172, 211};
const SDL_Color WHITE = {255, 255, 255};
const SDL_Color BG_COLOR = {28, 28, 28};

void load_text(SDL_Renderer *renderer, MenuItems *menu_items,
               int screen_width) {
  for (int i = 0; i < MENU_COUNT; i++) {
    if (i == menu_items->index)
      menu_items->surface[i] = TTF_RenderText_Solid(
          menu_items->font, menu_items->text[i], SEL_COLOR);
    else
      menu_items->surface[i] =
          TTF_RenderText_Solid(menu_items->font, menu_items->text[i], WHITE);

    menu_items->texture[i] =
        SDL_CreateTextureFromSurface(renderer, menu_items->surface[i]);

    SDL_QueryTexture(menu_items->texture[i], NULL, NULL, &menu_items->tex_w[i],
                     &menu_items->tex_h[i]);

    SDL_FreeSurface(menu_items->surface[i]);

    menu_items->rect[i].w = menu_items->tex_w[i];
    menu_items->rect[i].h = menu_items->tex_h[i];
    menu_items->rect[i].x = screen_width / 2 - menu_items->rect[i].w / 2;
  }
}

MenuItems create_menu(SDL_Renderer *renderer, int screen_width) {
  MenuItems menu_items;

  menu_items.text[0] = "Flappy Bird";
  menu_items.text[1] = "Pong";
  menu_items.text[2] = "Tetris";

  menu_items.index = 0;

  menu_items.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  menu_items.menu_sound = Mix_LoadWAV("assets/sounds/menu/menu_sound.mp3");

  if (menu_items.menu_sound == NULL)
    fprintf(stderr, "Failed to load enter sound: %s\n", SDL_GetError());

  menu_items.enter_sound = Mix_LoadWAV("assets/sounds/menu/enter_sound.mp3");

  if (menu_items.enter_sound == NULL)
    fprintf(stderr, "Failed to load enter sound: %s\n", SDL_GetError());

  TTF_SetFontHinting(menu_items.font, TTF_HINTING_LIGHT_SUBPIXEL);
  if (menu_items.font == NULL) {
    fprintf(stderr, "Failed to open font: %s\n", SDL_GetError());
  }

  load_text(renderer, &menu_items, screen_width);
  return menu_items;
}

void goto_menu(MenuItems *menu_items) { menu_items->index = 0; }

void render_text(SDL_Renderer *renderer, MenuItems *menu_items, int start_y,
                 int gapy) {
  int y = start_y;

  for (int i = 0; i < MENU_COUNT; i++) {
    menu_items->rect[i].y = y;
    SDL_RenderCopy(renderer, menu_items->texture[i], NULL,
                   &menu_items->rect[i]);
    y += gapy;
  }
}

void destroy_menu(MenuItems menu_items) {
  if (menu_items.font == NULL) {
    TTF_CloseFont(menu_items.font);
  }

  for (int i = 0; i < MENU_COUNT; i++) {
    SDL_DestroyTexture(menu_items.texture[i]);
  }
}

void menu_item_up(SDL_Renderer *renderer, MenuItems *menu_items,
                  int screen_width) {
  if (menu_items->index > 0) {
    menu_items->index--;
    load_text(renderer, menu_items, screen_width);
    Mix_PlayChannel(-1, menu_items->menu_sound, 0);
  }
}

void menu_item_down(SDL_Renderer *renderer, MenuItems *menu_items,
                    int screen_width) {
  if (menu_items->index < MENU_COUNT - 1) {
    menu_items->index++;
    load_text(renderer, menu_items, screen_width);
    Mix_PlayChannel(-1, menu_items->menu_sound, 0);
  }
}

void select_item(MenuItems *menu_items) {
  bool play_sound = true;

  switch (menu_items->index) {
  case 0:
    active_game_state = flappybird_state;
    break;
  default:
    play_sound = false;
    break;
  }

  if (play_sound)
    Mix_PlayChannel(-1, menu_items->enter_sound, 0);
}

void menu_events(SDL_Event e, SDL_Renderer *renderer, MenuItems *menu_items,
                 int screen_width) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      menu_item_up(renderer, menu_items, screen_width);
      break;
    case SDLK_DOWN:
      menu_item_down(renderer, menu_items, screen_width);
      break;
    case SDLK_RETURN:
      select_item(menu_items);
      break;
    }
  }
}

void render_menu(SDL_Renderer *renderer, MenuItems *menu_items) {
  SDL_RenderClear(renderer);
  render_text(renderer, menu_items, 100, FONT_SIZE * 1.56);
  SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b,
                         BG_COLOR.a);
  SDL_RenderPresent(renderer);
}
