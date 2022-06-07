#include "breakout.h"
#include "header.h"

game_state active_game_state = menu_state;
bool quit = false;

int main(void) {
  init_sdl2();

  MenuItems menu = create_menu(renderer, WIDTH);

  FlappyBird flappybird = create_bird(renderer, WIDTH, HEIGHT);

  Breakout breakout = create_breakout(renderer, WIDTH, HEIGHT);

  while (!quit) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
      switch (active_game_state) {
      case menu_state:
        menu_events(e, renderer, &menu, WIDTH);
        break;
      case flappybird_state:
        events_flappybird(e, renderer, WIDTH, HEIGHT, &flappybird);
        break;
      case breakout_state:
        events_breakout(e, renderer, WIDTH, HEIGHT, &breakout);
        break;
      }
    }

    switch (active_game_state) {
    case menu_state:
      render_menu(renderer, &menu);
      break;
    case flappybird_state:
      update_flappybird(WIDTH, HEIGHT, &flappybird);
      render_flappybird(renderer, flappybird);
      break;
    case breakout_state:
      update_breakout(WIDTH, HEIGHT, &breakout);
      render_breakout(renderer, breakout);
      break;
    }
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  destroy_menu(menu);
  destroy_flappybird(flappybird);
  return 0;
}
