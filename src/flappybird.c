#include "flappybird.h"

const SDL_Color SKY_COLOR = {50, 10, 155, 255};
const SDL_Color BIRD_COLOR = {255, 0, 0, 255};

const float GRAVITY = .1f;
const float MAX_VEL = 5.0f;
const float JUMP_HEIGHT = 5.0f;

const int INITIAL_BIRD_Y = 500;

const int TUBE_WIDTH = 150;
const int TUBE_Y_GAP = 250;
const int TUBE_X_GAP = 500;
const int MIN_X = 50;
const int MAX_X = 650;
const SDL_Color TUBE_COLOR = {0, 200, 155, 255};

int rand_range(int low, int high) { return low + (rand() % (high - low)); }

void create_tubes(int screen_width, int screen_height, FlappyBird *bird) {
  int tube_x = screen_width;

  for (int i = 0; i < MAX_TUBES; i++) {
    bird->bot_tubes[i] = (SDL_Rect){
        .w = TUBE_WIDTH,
        .h = rand_range(MIN_X, MAX_X),
        .x = tube_x,
    };

    bird->bot_tubes[i].y = screen_height - bird->bot_tubes[i].h;

    tube_x += TUBE_X_GAP;

    bird->top_tubes[i] = (SDL_Rect){.w = TUBE_WIDTH,
                                    .h = bird->bot_tubes[i].y - TUBE_Y_GAP,
                                    .x = bird->bot_tubes[i].x,
                                    .y = 0};
  }
}

void render_tubes(SDL_Renderer *renderer, FlappyBird bird) {
  SDL_SetRenderDrawColor(renderer, TUBE_COLOR.r, TUBE_COLOR.g, TUBE_COLOR.b,
                         TUBE_COLOR.a);

  SDL_RenderFillRects(renderer, bird.top_tubes, MAX_TUBES);
  SDL_RenderFillRects(renderer, bird.bot_tubes, MAX_TUBES);
}

FlappyBird create_bird(SDL_Renderer *renderer, int screen_width,
                       int screen_height) {
  FlappyBird flappybird;

  flappybird.flap_sound = Mix_LoadWAV("assets/sounds/flappybird/wing.wav");
  flappybird.rect = (SDL_Rect){
      .w = 50,
      .h = 50,
      .x = 100,
      .y = INITIAL_BIRD_Y,
  };

  flappybird.vel_y = 0;
  flappybird.can_jump = true;
  flappybird.scroll_speed = 2;
  flappybird.last_tube = MAX_TUBES - 1;
  flappybird.game_running = true;

  create_tubes(screen_width, screen_height, &flappybird);

  return flappybird;
}

void reset_flappybird(SDL_Renderer *renderer, int screen_width,
                      int screen_height, FlappyBird *bird) {
  destroy_flappybird(*bird);
  *bird = create_bird(renderer, screen_width, screen_height);
}

void end_game(FlappyBird *bird) { bird->game_running = false; }

void update_flappybird(int screen_width, int screen_height, FlappyBird *bird) {
  if (bird->game_running) {
    if (bird->vel_y < MAX_VEL)
      bird->vel_y += GRAVITY;
    bird->rect.y += bird->vel_y;

    for (int i = 0; i < MAX_TUBES; i++) {
      bird->top_tubes[i].x -= bird->scroll_speed;
      bird->bot_tubes[i].x -= bird->scroll_speed;

      if (SDL_HasIntersection(&bird->rect, &bird->top_tubes[i]) ||
          SDL_HasIntersection(&bird->rect, &bird->bot_tubes[i]) ||
          bird->rect.y + bird->rect.h > screen_height || bird->rect.y < 0) {
        end_game(bird);
      }

      if (bird->bot_tubes[i].x == -bird->bot_tubes[i].w) {
        bird->bot_tubes[i].x = bird->bot_tubes[bird->last_tube].x + TUBE_X_GAP;
        bird->bot_tubes[i].h = rand_range(MIN_X, MAX_X);
        bird->bot_tubes[i].y = screen_height - bird->bot_tubes[i].h;

        bird->top_tubes[i].h = bird->bot_tubes[i].y - TUBE_Y_GAP,
        bird->top_tubes[i].x = bird->bot_tubes[bird->last_tube].x + TUBE_X_GAP;

        bird->last_tube = i;
      }
    }
  }
}

void flappybird_jump(FlappyBird *bird) {
  if (bird->can_jump && bird->game_running) {
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
    case SDLK_r:
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
