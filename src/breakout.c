#include "breakout.h"

const SDL_Color BREAKOUT_BG_COLOR = {28, 28, 30, 255};

const int BALL_SIZE = 30;
const SDL_Color BALL_COLOR = {255, 255, 255, 255};

Breakout create_breakout(SDL_Renderer *renderer, int screen_width,
                         int screen_height) {
  Breakout breakout;

  breakout.ball = (SDL_Rect){
      .w = BALL_SIZE,
      .h = BALL_SIZE,
      .x = screen_width / 2,
      .y = screen_height / 2,
  };

  breakout.ball_speed = 2;
  breakout.xdir = 1;
  breakout.ydir = 1;

  return breakout;
}

void reset_breakout(SDL_Renderer *renderer, int screen_width, int screen_height,
                    Breakout *breakout) {
  *breakout = create_breakout(renderer, screen_width, screen_height);
}

void check_collision(int screen_width, int screen_height, Breakout *breakout) {
  if (breakout->ball.x >= screen_width - breakout->ball.w) breakout->xdir *= -1;
  if (breakout->ball.y >= screen_height - breakout->ball.h) breakout->ydir *= -1;
  if (breakout->ball.x <= 0) breakout->xdir *= -1;
  if (breakout->ball.y <= 0) breakout->ydir *= -1;
}

void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                     int screen_height, Breakout *breakout) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
      active_game_state = menu_state;
      break;
    case SDLK_LEFT:
      break;
    case SDLK_RIGHT:
      break;
    case SDLK_r:
      reset_breakout(renderer, screen_width, screen_height, breakout);
      break;
    }
  }
}

void update_breakout(int screen_width, int screen_height, Breakout *breakout) {
  check_collision(screen_width, screen_height, breakout);
  breakout->ball.x += breakout->xdir * breakout->ball_speed;
  breakout->ball.y += breakout->ydir * breakout->ball_speed;
}

void render_ball(SDL_Renderer *renderer, Breakout breakout) {
  SDL_SetRenderDrawColor(renderer, BALL_COLOR.r, BALL_COLOR.g, BALL_COLOR.b,
                         BALL_COLOR.a);

  SDL_RenderFillRect(renderer, &breakout.ball);
}

void render_breakout(SDL_Renderer *renderer, Breakout breakout) {
  SDL_RenderClear(renderer);

  render_ball(renderer, breakout);

  SDL_SetRenderDrawColor(renderer, BREAKOUT_BG_COLOR.r, BREAKOUT_BG_COLOR.g,
                         BREAKOUT_BG_COLOR.b, BREAKOUT_BG_COLOR.a);

  SDL_RenderPresent(renderer);
}
