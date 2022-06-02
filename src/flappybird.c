#include "flappybird.h"

const SDL_Color SKY_COLOR = {50, 10, 155, 255};
const SDL_Color BIRD_COLOR = {255, 0, 0, 255};

const float GRAVITY = .1f;
const float MAX_VEL = 5.0f;
const float JUMP_HEIGHT = 5.0f;

FlappyBird create_bird(SDL_Renderer *renderer, int screen_width) {
  FlappyBird flappybird;

  flappybird.flap_sound = Mix_LoadWAV("assets/sounds/flappybird/wing.wav");
  flappybird.rect = (SDL_Rect){
      .w = 100,
      .h = 100,
      .x = 100,
      .y = 500,
  };

  flappybird.vel_y = 0;
  flappybird.can_jump = true;

  return flappybird;
}

void update_bird(FlappyBird *bird) {
  if (bird->vel_y < MAX_VEL)
    bird->vel_y += GRAVITY;
  bird->rect.y += bird->vel_y;
}

void flappybird_jump(FlappyBird *bird) {
  if (bird->can_jump) {
    bird->vel_y = -JUMP_HEIGHT;
    Mix_PlayChannel(-1, bird->flap_sound, 0);
    bird->can_jump = false;
  }
}

void events_flappybird(SDL_Event e, FlappyBird *bird) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_SPACE:
      flappybird_jump(bird);
      break;
    }
  }
  else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) {
    bird->can_jump = true;
  }
}

void render_flappybird(SDL_Renderer *renderer, FlappyBird bird) {
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, BIRD_COLOR.r, BIRD_COLOR.g, BIRD_COLOR.b,
                         BIRD_COLOR.a);
  SDL_RenderFillRect(renderer, &bird.rect);

  SDL_SetRenderDrawColor(renderer, SKY_COLOR.r, SKY_COLOR.g, SKY_COLOR.b,
                         SKY_COLOR.a);
  SDL_RenderPresent(renderer);
}
