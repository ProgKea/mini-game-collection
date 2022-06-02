#include "flappybird.h"

const SDL_Color SKY_COLOR = {50, 10, 155, 255};
const SDL_Color BIRD_COLOR = {255, 0, 0, 255};

const float GRAVITY = .1f;
const float MAX_VEL = 5.0f;
const float JUMP_HEIGHT = 5.0f;

const int INITIAL_BIRD_Y = 500;

const int TUBE_WIDTH = 200;
const SDL_Color TUBE_COLOR = {0, 100, 155, 255};

void create_tubes(int screen_width, int screen_height, FlappyBird *bird) {
  int tube_x = screen_width;
  int gapx = 400;

  for (int i = 0; i < MAX_TUBES; i++) {
    bird->tubes[i] = (SDL_Rect){
        .w = TUBE_WIDTH,
        .h = 200,
        .x = tube_x,
    };

    bird->tubes[i].y = screen_height - bird->tubes[i].h;

    tube_x += gapx;
  }
}

void render_tubes(SDL_Renderer *renderer, FlappyBird bird) {
  SDL_SetRenderDrawColor(renderer, TUBE_COLOR.r, TUBE_COLOR.g, TUBE_COLOR.b,
                         TUBE_COLOR.a);

  SDL_RenderFillRects(renderer, bird.tubes, MAX_TUBES);
}

FlappyBird create_bird(SDL_Renderer *renderer, int screen_width,
                       int screen_height) {
  FlappyBird flappybird;

  flappybird.flap_sound = Mix_LoadWAV("assets/sounds/flappybird/wing.wav");
  flappybird.rect = (SDL_Rect){
      .w = 100,
      .h = 100,
      .x = 100,
      .y = INITIAL_BIRD_Y,
  };

  flappybird.vel_y = 0;
  flappybird.can_jump = true;
  flappybird.scroll_speed = 1.5f;

  create_tubes(screen_width, screen_height, &flappybird);

  return flappybird;
}

void reset_flappybird(SDL_Renderer *renderer, int screen_width,
                      int screen_height, FlappyBird *bird) {
  destroy_flappybird(*bird);
  *bird = create_bird(renderer, screen_width, screen_height);
}

void update_flappybird(FlappyBird *bird) {
  if (bird->vel_y < MAX_VEL)
    bird->vel_y += GRAVITY;
  bird->rect.y += bird->vel_y;

  for (int i = 0; i < MAX_TUBES; i++) {
    bird->tubes[i].x -= bird->scroll_speed;
  }
}

void flappybird_jump(FlappyBird *bird) {
  if (bird->can_jump) {
    bird->vel_y = -JUMP_HEIGHT;
    bird->can_jump = false;
    Mix_PlayChannel(-1, bird->flap_sound, 0);
  }
}

void events_flappybird(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                       int screen_height, FlappyBird *bird) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_SPACE:
      flappybird_jump(bird);
      break;
    case SDLK_ESCAPE:
      active_game_state = menu_state;
      reset_flappybird(renderer, screen_width, screen_height, bird);
      break;
    }
  } else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) {
    bird->can_jump = true;
  }
}

void render_flappybird(SDL_Renderer *renderer, FlappyBird bird) {
  SDL_RenderClear(renderer);

  render_tubes(renderer, bird);
  SDL_SetRenderDrawColor(renderer, BIRD_COLOR.r, BIRD_COLOR.g, BIRD_COLOR.b,
                         BIRD_COLOR.a);
  SDL_RenderFillRect(renderer, &bird.rect);
  SDL_SetRenderDrawColor(renderer, SKY_COLOR.r, SKY_COLOR.g, SKY_COLOR.b,
                         SKY_COLOR.a);

  SDL_RenderPresent(renderer);
}

void destroy_flappybird(FlappyBird bird) { Mix_FreeChunk(bird.flap_sound); }
