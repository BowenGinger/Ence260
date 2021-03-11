/*
 * File: symbol_choose.c
 * Author: Bowen, Zara
 * Date: 7/10/2020
 * Brief: use the navswitch to select either ROCK, PAPER or SCISSOR Symbols based on direction
 * Or cycle through symbols using down {SOUTH] direction
 */

#include <avr/io.h>
#include "outcome.h"
#include "symbol.h"

#include "navswitch.h"
#include "system.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "pacer.h"

symbol_t get_symbol(symbol_t local_symbol);
void display_symbol(symbol_t symbol);
int button_pressed_p (void);

/* Displays a single character (R\P\S) on the screen */
void display_symbol(symbol_t symbol)
{
    char buffer[2];
    buffer[0] = symbol;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

/* choose symbol and returns it if the navswitch was pressed
 * North for Rock, South for Paper, East for Scissor and West will switch between three status
 */
symbol_t get_symbol(symbol_t current_symbol)
{
    symbol_t symbol = current_symbol;

    if (navswitch_push_event_p(NAVSWITCH_NORTH)==1) {           /* Pushing nav switch up [NORTH] results in matrix displaying 'R' for rock symbol */
        symbol = ROCK;
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)==1) {            /* Pushing nav switch left [WEST] results in matrix displaying 'P' for paper symbol */
        symbol = PAPER;
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)==1) {            /* Pushing nav switch right [EAST] results in matrix displaying 'S' for scissor symbol */
        symbol = SCISSOR;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)==1) {           /* Pushing nav switch down [SOUTH] results in matrix cycling through displayed symbols, in order R, P, S repeating*/
        if (symbol == PAPER){
            symbol = SCISSOR;
        } else if (symbol == SCISSOR){
            symbol = ROCK;
        } else if (symbol == ROCK){
            symbol = PAPER;
        }

    }

    return symbol;
}
int button_pressed_p (void)
{
    /* TODO.  */

if ((PIND & (1<<7))!=0){
return 1;
}
return 0;
}