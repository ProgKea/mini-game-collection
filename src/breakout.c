#include "breakout.h"
#include <SDL2/SDL_render.h>

#define Color(color) color.r, color.g, color.b, color.a

const SDL_Color BREAKOUT_BG_COLOR = {28, 28, 30, 255};

const int BALL_SIZE = 30;
const SDL_Color BALL_COLOR = {255, 255, 255, 255};

const int PLAYER_WIDTH = 200;
const int PLAYER_HEIGHT = 10;
const int PLAYER_SPEED = 20;
const SDL_Color PLAYER_COLOR = {255, 28, 28, 255};

const int TARGET_WIDTH = 90;
const int TARGET_HEIGHT = 30;
const int TARGET_X_GAP = 10 + TARGET_WIDTH;
const int TARGET_Y_GAP = 10 + TARGET_HEIGHT;

void create_targets(int screen_width, int screen_height, Breakout *breakout) {
  int target_x = TARGET_X_GAP;
  int target_y = TARGET_Y_GAP;

  for (int i = 0; i < MAX_TARGETS; i++) {
    breakout->targets[i].killed = false;

    breakout->targets[i].rect = (SDL_Rect){
        .w = TARGET_WIDTH,
        .h = TARGET_HEIGHT,
        .x = target_x,
        .y = target_y,
    };

    breakout->targets[i].color = PLAYER_COLOR;
  }
}

Breakout create_breakout(SDL_Renderer *renderer, int screen_width,
                         int screen_height) {
  Breakout breakout;

  breakout.ball = (SDL_Rect){
      .w = BALL_SIZE,
      .h = BALL_SIZE,
      .x = screen_width / 2,
      .y = screen_height / 2,
  };

  breakout.player = (SDL_Rect){.w = PLAYER_WIDTH,
                               .h = PLAYER_HEIGHT,
                               .x = screen_width / 2 - PLAYER_WIDTH / 2,
                               .y = screen_height - 60};

  breakout.ball_speed = 2;
  breakout.xdir = 1;
  breakout.ydir = 1;
  breakout.game_running = true;

  create_targets(screen_width, screen_height, &breakout);

  return breakout;
}

void reset_breakout(SDL_Renderer *renderer, int screen_width, int screen_height,
                    Breakout *breakout) {
  *breakout = create_breakout(renderer, screen_width, screen_height);
}

void end_game_breakout(Breakout *breakout) { breakout->game_running = false; }

void check_collision(int screen_width, int screen_height, Breakout *breakout) {
  if (breakout->ball.x >= screen_width - breakout->ball.w)
    breakout->xdir *= -1;
  if (breakout->ball.y >= screen_height - breakout->ball.h)
    end_game_breakout(breakout);
  // breakout->ydir *= -1;
  if (breakout->ball.x <= 0)
    breakout->xdir *= -1;
  if (breakout->ball.y <= 0)
    breakout->ydir *= -1;

  if (SDL_HasIntersection(&breakout->player, &breakout->ball))
    breakout->ydir = -1;
}

void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                     int screen_height, Breakout *breakout) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
      reset_breakout(renderer, screen_width, screen_height, breakout);
      active_game_state = menu_state;
      break;
    case SDLK_LEFT:
      if (breakout->player.x > 0)
        breakout->player.x -= PLAYER_SPEED;
      else
        breakout->player.x = 0;
      break;
    case SDLK_RIGHT:
      if (breakout->player.x < screen_width - breakout->player.w)
        breakout->player.x += PLAYER_SPEED;
      else
        breakout->player.x = screen_width - breakout->player.w;
      break;
    case SDLK_r:
      reset_breakout(renderer, screen_width, screen_height, breakout);
      break;
    }
  }
}

void update_breakout(int screen_width, int screen_height, Breakout *breakout) {
  if (breakout->game_running) {
    check_collision(screen_width, screen_height, breakout);
    breakout->ball.x += breakout->xdir * breakout->ball_speed;
    breakout->ball.y += breakout->ydir * breakout->ball_speed;
  }
}

void render_ball(SDL_Renderer *renderer, Breakout breakout) {
  SDL_SetRenderDrawColor(renderer, Color(BALL_COLOR));

  SDL_RenderFillRect(renderer, &breakout.ball);
}

void render_player(SDL_Renderer *renderer, Breakout breakout) {
  SDL_SetRenderDrawColor(renderer, Color(PLAYER_COLOR));
  SDL_RenderFillRect(renderer, &breakout.player);
}

void render_targets(SDL_Renderer *renderer, Breakout breakout) {
  for (int i = 0; i < MAX_TARGETS; i++) {
    if (!breakout.targets[i].killed) {
      SDL_SetRenderDrawColor(renderer, Color(breakout.targets[i].color));

      SDL_RenderFillRect(renderer, &breakout.targets[i].rect);
    }
  }
}

void render_breakout(SDL_Renderer *renderer, Breakout breakout) {
  SDL_RenderClear(renderer);

  render_ball(renderer, breakout);
  render_player(renderer, breakout);
  render_targets(renderer, breakout);

  SDL_SetRenderDrawColor(renderer, Color(BREAKOUT_BG_COLOR));

  SDL_RenderPresent(renderer);
}
