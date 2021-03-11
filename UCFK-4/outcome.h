/*
 * File: outcome.h
 * Author: Bowen, Zara
 * Date: 07/10/2020
 * Brief: This is the typedef of the game results
 */


/* Use outcome_t to generate the outcome for the game */

#ifndef compare_H
#define compare_H
#include "symbol.h"

typedef enum {

    WIN,
    LOSE,
    DRAW

} outcome_t;

outcome_t compare(symbol_t local_symbol, symbol_t opponent_symbol);

#endif /* compare_H */