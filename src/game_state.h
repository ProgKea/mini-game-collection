#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum game_state { menu_state = 0, flappybird_state = 1, breakout_state = 2 } game_state;

extern game_state active_game_state;
extern bool quit;

#endif
