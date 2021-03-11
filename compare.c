/*
 * File: compare.c
 * Author: Bowen, Zara
 * Date: 07/10/2020
 * Brief: Compare two players chosen symbols and return either: WIN LOSE or DRAW depending on set interactions
 */

#include "navswitch.h"
#include "compare.h"
#include "pacer.h"
#include "symbol.h"
#include "outcome.h"
#include "tinygl.h"
outcome_t compare(symbol_t local_symbol, symbol_t opponent_symbol);

/* returns the result of the game, either: WIN, LOSE or Draw */
outcome_t compare(symbol_t local_symbol, symbol_t opponent_symbol)
{
    if (local_symbol == opponent_symbol) {                                  /* Players have chosen the same symbol resulting in a draw */
        return DRAW;
    } else if ((local_symbol == PAPER && opponent_symbol == ROCK)           /* Local player has chosen a symbol that wins against opponent */
            || (local_symbol == ROCK && opponent_symbol == SCISSOR)         /* ^ Ditto */
            || (local_symbol == SCISSOR && opponent_symbol == PAPER)) {     /* ^ Ditto */
        return WIN;
    } else {
        return LOSE;                                                        /* Else local player has chosen a symbol that loses against opponent */
    }
}