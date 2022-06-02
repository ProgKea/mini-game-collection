#include "header.h"

game_state active_game_state = menu_state;

int main(void) {
  init_sdl2();

  MenuItems menu = create_menu(renderer, WIDTH);

  FlappyBird flappybird = create_bird(renderer, WIDTH);

  while (1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        break;
      switch (active_game_state) {
      case menu_state:
        menu_events(e, renderer, &menu, WIDTH);
        break;
      case flappybird_state:
        events_flappybird(e, &flappybird);
        break;
      }
    }

    switch (active_game_state) {
      case menu_state:
        render_menu(renderer, &menu);
        break;
      case flappybird_state:
        update_bird(&flappybird);
        render_flappybird(renderer, flappybird);
        break;
    }
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  destroy_menu(menu);
  return 0;
}
