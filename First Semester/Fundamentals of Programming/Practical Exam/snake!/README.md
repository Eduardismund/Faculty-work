# Snake!

**Snake!** is a console-based game where the player controls a snake to eat apples and grow while avoiding collisions with the wall or itself. The game is implemented using Python 3 and follows an object-driven layered architecture.

## Program Overview

### 1. Game Initialization

- **Game Area Display**: At the start of the game, display the game area, which is an \( N \times N \) matrix.
  - The snake starts with:
    - A head segment represented by `*`.
    - Two body segments represented by `+`.
  - The snake is initially placed in the middle of the board.
  - Apples are represented by `(a)`.
  - Apples are placed randomly on the board with the following constraints:
    - Two apples cannot be adjacent in the same row or column.
    - Apples cannot overlap with the snake's starting position.
  - The value of \( N \) and the number of apples are read from a settings file, and it is assumed that these values are correct.

  **Example:**
  - For a 10x10 board, the initial game area might look like this:
    ```
    ......... 
    ......... 
    ......... 
    ....*+... 
    ....+.... 
    ......... 
    ......... 
    ......... 
    ......... 
    ......... 
    ```

### 2. Game Commands

- **Movement**:
  - `move [n]`: Moves the snake \( n \) squares in the current direction. If no parameter is provided, the snake moves by 1 square.
  - Valid directions are `up`, `right`, `down`, and `left`. Changing direction by 180 degrees results in an error message.
  - Changing direction to the current direction does nothing.

  **Examples:**
  - `move 3`: Moves the snake 3 squares in its current direction.
  - `right`: Changes the snake’s direction to the right.

- **Direction Change**:
  - `up`: Changes the snake’s direction to up.
  - `right`: Changes the snake’s direction to the right.
  - `down`: Changes the snake’s direction to down.
  - `left`: Changes the snake’s direction to the left.
  
  **Error Handling:**
  - Trying to change direction to the opposite of the current direction should display an error message.
  - Example: If the snake is moving `up`, trying to change direction to `down` results in an error.

### 3. Eating Apples

- When the snake eats an apple:
  - The snake's tail grows by 1 square.
  - A new apple is placed on the board following the same rules as the initial apple placement.

  **Example:**
  - If the snake eats an apple, the game area updates to show the snake's new length and the new apple's position.

### 4. Game End Conditions

- The game ends when:
  - The snake hits the edge of the game area.
  - The snake collides with one of its own segments.

  **Example:**
  - If the snake runs into a wall or itself, the game should display a message indicating the end of the game.

## Non-Functional Requirements

- **Layered Architecture**: Implement the game using a layered architecture, separating concerns into different components.
- **Code Quality**: The solution should include well-defined functions with appropriate parameters, maintain readability, and follow good coding practices.
- **Error Handling**: Ensure that all user inputs and commands are validated and handled gracefully.

## Example Gameplay

**Initial State**:

    ```
    ......... 
    ......... 
    ......... 
    ....*+... 
    ....+.... 
    ......... 
    ......... 
    ......... 
    ......... 
    ......... 
    ```

    
**Commands and Results**:

1. Command: `move 2`
   - Result: Snake moves 2 squares in the current direction.

2. Command: `right`
   - Result: Changes direction to the right.

3. Command: `move 1`
   - Result: Snake moves 1 square to the right.

4. Command: `up`
   - Result: Changes direction to up.

5. Command: `move 1`
   - Result: Snake moves 1 square up. If it hits an apple, it grows and a new apple appears.

6. Command: `down`
   - Result: Error message if trying to reverse direction.

7. **Game End**: If the snake collides with the wall or itself, display `"Game Over"` and the final score.

