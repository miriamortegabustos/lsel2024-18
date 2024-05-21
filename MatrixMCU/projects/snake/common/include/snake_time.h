#ifndef _SNAKE_TIME_H
#define _SNAKE_TIME_H

#include "snake.h"
#include <stdint.h>

/*Inicializacion del tiempo*/
int snake_time_init (snake_game_t* p_game);
/*Desinicializacion del tiempo*/
void snake_time_close ();
/*Espera activa de ms*/
void snake_time_delay_ms (uint32_t ms);

#endif
