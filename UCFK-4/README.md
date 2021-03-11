# This is the group-525 ENCE260 embedded systems assignment.
## Author: Bowen Jiang, Zara Smith


# Instructions and How to play:
The game developed, is a Rock, Paper, Scissors Game.<br>
Players will choose between three symbols: R, P, S  which represent Rock, Paper, and Scissors respectively<br>
These symbols will be displayed on the UCFK 4 LED matrix<br>
The default value upon initialisation has been set to Rock, represented by 'R'<br>


-------
## The player can use the navigation switch to select between the three symbols:

UP [North] sets the symbol to Rock, represented by 'R'<br>
LEFT (West) sets the symbol to Paper, represented by 'P'<br>
RIGHT [East] sets the symbol to Scissors, represented by 'S'<br>
DOWN (South) is used to cycle between the three symbols in order R, P, S<br><br>

Pushing down on the navigation switch will comfirm the player's chosen symbol.<br>
The UCFK 4 will then send the signal to the opponent's UCFK 4, and wait to receive the  opponent's signal in return.<br>
Whilst the UCFK 4 is waiting to recieve the opponent's signal, the matrix will display a * symbol, and the blue LED will turn on. <br>
Once both UCFK 4, have sent and recieved eachothers signals, the devices will calculate the game result.<br>
Game result can be 'WIN' 'LOSE' 'DRAW' <br>
The respective results will be displayed on the respective UCFK 4 LED matrix<br><br>

To restart the game, players can push down on the navigation switch, or press on switch 1.<br><br>


--------
# Program Structure

This program has five parts {game.c, symol_choose.c, compare.c, symbol.h, compare.h}<br>
It includes call functions in Driver and Utils which are pre-built in the folder.<br><br><br>



# Ence260
