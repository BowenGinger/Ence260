/*
 * File: game.c
 * Author: Bowen, Zara
 * Date: 07/10/2020
 * Brief: This is the Ence260 ES assignment and this is a paper-rock-scissors game
 * Players use the navswitch to choose between symbols, press down on the navswitch to select their symbol, and press switch 1 to reset the game
 * Game is played between two UCFK 4
 */

//#include "symbol_choose.c"
//#include "compare.c"
#include "outcome.h"
#include "symbol.h"
#include "outcome.h"

#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include <avr/io.h>

#define PACER_LOOP_RATE 1000
#define DISPLAY_LOOP_RATE 1000
#define DISPLAY_MESSAGE_RATE 2

int main (void)   /* MAIN PROGRAM */
{

    /* Initialize what the game needs */
    system_init();                                  /* Initialize in system.h */
    navswitch_init();                               /* Initialization of the navigation switch */
    ir_uart_init();                                 /* Initialization of the infrared sender and recever */
    pacer_init(PACER_LOOP_RATE);                    /* Initialization of the pacer loop rate 1000 */
    tinygl_init(DISPLAY_LOOP_RATE);                 /* Initialization of the tinygl loop rate 1000 */
    tinygl_font_set(&font5x7_1);                    /* Set the led matrix display messagefont */
    tinygl_text_speed_set(DISPLAY_MESSAGE_RATE);    /* Set the led matrix display message speed 20 */
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);  /* Set the led matrix display message scroll mode */
    DDRC |=(1<<2);                                  /* Initialise port to drive LED 1.  */
    DDRD &= ~(1<<7);                                /* Initialise port to drive switch 1, used for restarting the game  */

    int sent = 0;               /* Initialization sent = 0, the symbol is sent or not */
    int received = 0;           /* Initialization received = 0, symbol is recieved or not*/
    int chosen = 0;             /* Initialization the chosen equal 0, this is the status for the user - whether they have chosen or not */
    int result = 0;             /* Initialization the result = 0 for both players, result are Win-Lose-Draw */

    symbol_t rec_symbol;            /* Used for the received symbol */
    symbol_t local_symbol = ROCK;   /* Used for the local symbol */
    symbol_t opponent_symbol = 0;       /* Used for the opponents symbol */




    while (1)
    {
        navswitch_update();         /* Refresh the navigation switch */

        /* If the player hasn't chosen a symbol yet, allow the player to choose between three pre-set choices */
        if (chosen == 0) {

            local_symbol = get_symbol(local_symbol);    /* Let the player choose a symbol */

            display_symbol(local_symbol);               /* Whilst the player chooses their symbol the led matrix will display the current symbol */

            /* Player confirms the selected symbol */
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                tinygl_clear();                         /* Reset the GL display */
                chosen = 1;                             /* Set the chosen to 1 meaning player has already chosen */
            }
        }

        /* If chosen = 1, then the player has chosen a symbol */
        else if (sent == 0) {
            ir_uart_putc(local_symbol);                 /* Transmit the symbol */
            sent = 1;                                   /* Sent = 1 means the symbol has been sent */
        }


        /* Recieved = 0 means opponents symbol has not been recieved yet, but chosen symbol has been transmitted */
        if ((received == 0) && (sent == 1)) {
            tinygl_text("*");                           /* Set the LED matrix to * when waiting for opponent's signal */
            PORTC |= (1<<2);                            /* Turn on the blue LED when waiting for opponent's signal */
        }


        /* Device is trying to recieve signal constantly */
        if ((received == 0)) {
            if (ir_uart_read_ready_p()) {
                rec_symbol = ir_uart_getc(); /* Set the received signal as the opponents symbol */

                /* Check the received symbol is valid */
                if (rec_symbol == PAPER || rec_symbol == SCISSOR || rec_symbol == ROCK) {
                    opponent_symbol = rec_symbol;           /* Set a valid signal as the opponent_symbol */
                    received = 1;                       /* Received = 1 means the symbol has been received */
                }
            }
        }
        tinygl_update();                                /* Update the GL */

        /* When device is ready to determine the outcome between the three statuses which are win, lose and draw */
        if ((sent == 1)&& (received == 1)) {
            PORTC &= ~(1<<2);                           /* Turn off the blue LED after opponent's signal is recieved */
            if (result == 0) {

                /* Compare the local symbol and the opponents symbol */
                if (compare(local_symbol, opponent_symbol) == WIN) {
                        tinygl_text("WIN");                         /* Set the text to 'WIN' in the LED matrix */
                        result = 1;                                 /* Result = 1 means the result is determined */
                } else if (compare(local_symbol, opponent_symbol) == LOSE) {
                        tinygl_text("LOSE");                        /* Set the text to 'LOSE' in the LED matrix */
                        result = 1;                                 /* Result = 1 means the result is determined */
                } else if (compare(local_symbol, opponent_symbol) == DRAW) {
                        tinygl_text("DRAW");                        /* Set the text to 'DRAW' in the LED matrix */
                        result = 1;                                 /* Result = 1 means the result is determined */
                }
            }

            /* Restart the game after result, set the all values to the default values
             * By pressing the navswitch down or pushing switch 1
             * Reset all statuses to equal 0 and display the symbol R */
            if (navswitch_push_event_p(NAVSWITCH_PUSH) || button_pressed_p()) {
                sent = 0;
                received = 0;
                chosen = 0;
                result = 0;
                local_symbol = ROCK;
            }
        }
        /* Restart the game at any time by pushing switch 1, set the all values to the default values */
        if (button_pressed_p()) {
                PORTC &= ~(1<<2);
                sent = 0;
                received = 0;
                chosen = 0;
                result = 0;
                local_symbol = ROCK;
        }
        tinygl_update();        /* Update the GL */
    }
}