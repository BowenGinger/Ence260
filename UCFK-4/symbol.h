/*
 * File: symbol.h
 * Author: Bowen, Zara
 * Date: 07/10/2020
 * Brief: This is the typedef of the choosable symbols
 */

/* Create and assign the symbols R,P,S to represent ROCK, PAPER and SCISSORS respectively */
#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef enum {

    ROCK = 'R',
    PAPER = 'P',
    SCISSOR = 'S'

} symbol_t;


symbol_t get_symbol(symbol_t local_symbol);
void display_symbol(symbol_t symbol);
int button_pressed_p (void);


#endif /* SYMBOLS_H */
