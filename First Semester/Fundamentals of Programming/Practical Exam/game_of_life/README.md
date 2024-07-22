# Game of Life

## Overview
The Game of Life is a cellular automaton developed by John Conway in 1970. This zero-player game simulates the evolution of a grid of cells based on an initial configuration provided by the user. The game runs autonomously, requiring no further input once started.

## Rules
The game operates on an 8x8 grid where each cell can be either alive (`X`) or dead (empty). The evolution of the grid follows these rules:
1. **Under-population**: Any live cell with fewer than 2 live neighbors dies.
2. **Survival**: Any live cell with 2 or 3 live neighbors lives on to the next generation.
3. **Over-population**: Any live cell with more than 3 live neighbors dies.
4. **Reproduction**: Any dead cell with exactly 3 live neighbors becomes a live cell.

Neighbors include the cells directly adjacent and diagonal to a cell.

## Functional Requirements
1. **Initialization**: 
   - Start with an empty 8x8 grid.
   - Display the grid.
   - Allow users to add cell patterns to the grid at any time.

2. **Pattern Placement**:
   - Load patterns from a read-only text file.
   - Add a pattern using the command: `place <pattern> <x,y>`, specifying the upper left corner of the pattern.
   - Ensure patterns do not extend beyond the grid boundaries.

3. **Simulation Control**:
   - Create new generations with the `tick [n]` command, where `n` specifies the number of generations to advance. The default is 1.
   - Save the current grid state using the `save <filename>` command.
   - Load a saved grid state with the `load <filename>` command.

## Non-functional Requirements
- Ensure the program does not crash regardless of user input.
- Implement a layered architecture solution using Python 3, classes, and objects.
- Provide specifications and tests for functionality 3. Note: If specifications or tests are missing, the functionality is not graded.

## Default Patterns
Default pattern examples and their placements are provided in the text file.

---

