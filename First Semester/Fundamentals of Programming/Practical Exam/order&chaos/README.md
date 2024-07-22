# Order and Chaos Game

## Overview

**Order and Chaos** is a strategy game played on a 6x6 board. The two players are:
- **Order** (human player) who wins by aligning 5 consecutive pieces of the same type in a row, column, or diagonal.
- **Chaos** (computer player) who wins if the board is filled up without Order achieving the alignment.

### Program Features

1. **Display the Board**: Show the 6x6 board when the program starts.
2. **Turn-Based Play**: Order (the human player) takes the first move, followed by Chaos (the computer player).
3. **Move Validation**: Ensure user input is valid and display an error message for illegal moves.
4. **Computer Moves**: The computer makes random but valid moves, and attempts to block Order's winning moves whenever possible.
5. **Winning Conditions**: Check for 5 consecutive symbols in rows, columns, or diagonals.
6. **Game End**: Declare Chaos as the winner if the board is full and Order hasn’t won.
7. **Save and Load**: Save the game state to a file and allow the game to continue from the saved state.
