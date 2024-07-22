# Scramble!

**Scramble!** is a console-based game where the objective is to unscramble a sentence by swapping pairs of letters, while keeping the first and last letters of each word in place. 

## Program Functionality

1. **Start a New Game**

   - Each time the program starts, a new game begins.
   - The word or sentence is selected randomly from a text file.
   - The program scrambles the word or sentence by keeping the first and last letter of each word in place, while shuffling the rest of the letters randomly.
   - The initial score is equal to the number of letters in the given word or sentence (excluding spaces).

   **Example:**
   - Input Sentence: `"Dream without fear"`
   - Scrambled Sentence: `"Doahm wueirtt feae"`
   - Initial Score: `16`

2. **Swapping Letters**

   - The user can swap two letters using the command: `swap <word_index> <letter_index1> <letter_index2>`
   - `word_index` indicates which word in the sentence to operate on.
   - `letter_index1` and `letter_index2` specify the positions of the letters to be swapped.
   - After each swap, the updated sentence is displayed, and the score decreases by 1.

   **Example:**
   - Command: `swap 01-03`
   - Updated Sentence: `"Drahs wueiott fear"`
   - Updated Score: `15`

   **Error Handling:**
   - If the command is incomplete, or indices are incorrect or include the first or last letter of a word, an error message is displayed.

3. **Undo Last Swap**

   - The user can undo the last swap operation using the command: `undo`
   - This command reverts the last swap without affecting the score.

   **Example:**
   - After undoing the previous swap: `"Drahn woeiott fear"`
   - Score remains the same: `14`

4. **Game End Conditions**

   - The game ends when one of the following conditions is met:
     - The score reaches 0 (defeat).
     - The sentence is unscrambled correctly (victory).
   - The player receives a corresponding message based on the game outcome.

   **Example:**
   - Final Sentence: `"Dream without fear"`
   - Final Score: `9`
   - Message: `"You won! Your score is 9"`

## Example Gameplay

**Initial Sentence:**
- `"dream without fear"`
- Scrambled: `"Doahm wuelrtt fear"`
- Score: `16`

**Commands and Results:**

1. `swap 01-14`
   - Result: `"Drahs wueiott fear"`
   - Score: `15`

2. `swap 03-11`
   - Result: `"Drahn woeiott fear"`
   - Score: `14`

3. `undo`
   - Result: `"Drahs wueiott fear"`
   - Score remains: `14`

4. `swap 02-03`
   - Result: `"Drham woeiott fear"`
   - Score: `12`

5. `swap 02-11`
   - Result: `"Dream woeiott fear"`
   - Score: `12`

6. `swap 12-15`
   - Result: `"Dream withoot fear"`
   - Score: `10`

7. `swap 13-15`
   - Result: `"Dream without fear"`
   - Score: `9`
   - Message: `"You won! Your score is 9"`

## Non-Functional Requirements

- The program must handle invalid commands gracefully.
- The game must ensure that all operations are executed correctly, and the user interface should clearly show the results and scores.
- The implementation should follow best practices for modularity and error handling.

