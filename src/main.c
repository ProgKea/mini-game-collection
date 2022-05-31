#include "header.h"

int main(void) {
  init_sdl2();

  while (1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        break;
      if (is_menu)
        menu_events(e, renderer, WIDTH);
    }

    if (is_menu) {
      render_menu(renderer);
    }
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  destroy_menu();
  return 0;
}
