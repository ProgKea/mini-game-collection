#include "breakout.h"

#define Color(color) color.r, color.g, color.b, color.a

const SDL_Color BREAKOUT_BG_COLOR = {28, 28, 30, 255};

const int BALL_SIZE = 30;
const SDL_Color BALL_COLOR = {255, 255, 255, 255};

const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 20;
const int PLAYER_SPEED = 6;
const SDL_Color PLAYER_COLOR = {255, 28, 28, 255};

const int TARGET_X_GAP = 20;
const int TARGET_Y_GAP = 20;
const SDL_Color TARGET_COLOR = {0, 170, 30, 255};

double clamp(double d, double min, double max)
{
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

void create_targets(int screen_width, int screen_height, Breakout *breakout)
{
    int target_x = TARGET_X_GAP;
    int target_y = TARGET_Y_GAP;
    int target_width = (screen_width - TARGET_X_GAP) / TARGET_ROWS - TARGET_X_GAP;
    int target_height = target_width * 0.1;

    for (int col = 0; col < TARGET_COLS; col++) {
        for (int row = 0; row < TARGET_ROWS; row++) {
            breakout->targets[col][row].killed = false;

            breakout->targets[col][row].rect = (SDL_Rect){
                .w = target_width,
                .h = target_height,
                .x = target_x,
                .y = target_y,
            };

            breakout->targets[col][row].color = TARGET_COLOR;
            target_x += TARGET_X_GAP + target_width;
        }
        target_x = TARGET_X_GAP;
        target_y += TARGET_Y_GAP + target_height;
    }
}

Breakout create_breakout(SDL_Renderer *renderer, int screen_width, int screen_height)
{
    Breakout breakout;

    breakout.player = (SDL_Rect){
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .x = screen_width / 2 - PLAYER_WIDTH / 2,
        .y = screen_height - PLAYER_HEIGHT - 10
    };

    breakout.ball = (SDL_Rect){
        .w = BALL_SIZE,
        .h = BALL_SIZE,
        .x = breakout.player.x + breakout.player.w / 2 - BALL_SIZE / 2,
        .y = breakout.player.y - BALL_SIZE,
    };

    breakout.player_xdir = 0;
    breakout.ball_speed = 3;
    breakout.ball_xdir = 1;
    breakout.ball_ydir = 1;
    breakout.ball_attached = true;
    breakout.game_running = true;

    create_targets(screen_width, screen_height, &breakout);

    return breakout;
}

void reset_breakout(SDL_Renderer *renderer, int screen_width, int screen_height, Breakout *breakout)
{
    *breakout = create_breakout(renderer, screen_width, screen_height);
}

void end_game_breakout(Breakout *breakout) { breakout->game_running = false; }

void check_collision(int screen_width, int screen_height, Breakout *breakout)
{
    if (breakout->ball.x >= screen_width - breakout->ball.w)
    breakout->ball_xdir *= -1;
    if (breakout->ball.y >= screen_height - breakout->ball.h)
    end_game_breakout(breakout);
    if (breakout->ball.x <= 0)
    breakout->ball_xdir *= -1;
    if (breakout->ball.y <= 0)
    breakout->ball_ydir *= -1;

    for (int col = 0; col < TARGET_COLS; col++) {
        for (int row = 0; row < TARGET_ROWS; row++) {
            if (SDL_HasIntersection(&breakout->targets[col][row].rect, &breakout->ball) && !breakout->targets[col][row].killed) {
                breakout->targets[col][row].killed = true;
                breakout->ball_ydir *= -1;
            }
        }
    }

    if (SDL_HasIntersection(&breakout->player, &breakout->ball)) {
        if (breakout->player_xdir != 0) {
            breakout->ball_xdir = breakout->player_xdir;
        }
        breakout->ball_ydir = -1;
    }
}

void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width, int screen_height, Breakout *breakout)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
            reset_breakout(renderer, screen_width, screen_height, breakout);
            active_game_state = menu_state;
            break;
            case SDLK_LEFT:
            case SDLK_a:
            breakout->player_xdir = -1;
            break;
            case SDLK_RIGHT:
            case SDLK_d:
            breakout->player_xdir = 1;
            break;
            case SDLK_r:
            reset_breakout(renderer, screen_width, screen_height, breakout);
            break;
            case SDLK_SPACE:
            breakout->ball_attached = false;
            break;
        }
    }
}

void update_breakout(int screen_width, int screen_height, Breakout *breakout)
{
    if (breakout->game_running) {
        check_collision(screen_width, screen_height, breakout);
        if ((breakout->player.x < screen_width - breakout->player.w && breakout->player_xdir != -1) || (breakout->player.x > 0 && breakout->player_xdir != 1)) {
            breakout->player.x += breakout->player_xdir * PLAYER_SPEED;
        }
        if (!breakout->ball_attached) {
            breakout->ball.x += breakout->ball_xdir * breakout->ball_speed;
            breakout->ball.y += breakout->ball_ydir * breakout->ball_speed;
        }
        else {
            breakout->ball.x = breakout->player.x + breakout->player.w / 2 - BALL_SIZE / 2;
        }
    }
}

void render_ball(SDL_Renderer *renderer, Breakout breakout)
{
    SDL_SetRenderDrawColor(renderer, Color(BALL_COLOR));

    SDL_RenderFillRect(renderer, &breakout.ball);
}

void render_player(SDL_Renderer *renderer, Breakout breakout)
{
    SDL_SetRenderDrawColor(renderer, Color(PLAYER_COLOR));
    SDL_RenderFillRect(renderer, &breakout.player);
}

void render_targets(SDL_Renderer *renderer, Breakout breakout)
{
    for (int col = 0; col < TARGET_COLS; col++) {
        for (int row = 0; row < TARGET_ROWS; row++) {
            if (!breakout.targets[col][row].killed) {
                SDL_SetRenderDrawColor(renderer, Color(breakout.targets[col][row].color));

                SDL_RenderFillRect(renderer, &breakout.targets[col][row].rect);
            }
        }
    }
}

void render_breakout(SDL_Renderer *renderer, Breakout breakout)
{
    SDL_RenderClear(renderer);

    render_ball(renderer, breakout);
    render_player(renderer, breakout);
    render_targets(renderer, breakout);

    SDL_SetRenderDrawColor(renderer, Color(BREAKOUT_BG_COLOR));

    SDL_RenderPresent(renderer);
}
