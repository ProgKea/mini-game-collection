#include "header.h"

int main(void) {
  init_sdl2();

  SDL_Font menu_items = create_menu(renderer, WIDTH);

  while (1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        break;
      if (is_menu)
        menu_events(e, renderer, &menu_items, WIDTH);
    }

    if (is_menu) {
      render_menu(renderer, &menu_items);
    }
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  destroy_menu(menu_items);
  return 0;
}
