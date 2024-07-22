# Hangman Game

## Overview

You have to implement a console-based variation of the classical Hangman game. The computer will select a sentence that the user can attempt to guess, letter by letter. Each time the user guesses a correct letter, the computer will fill it in the sentence at the correct positions. If the letter does not appear, the computer will add a new letter to the word "hangman," starting from the empty string. The game ends when the user has guessed the sentence (user wins) or when the computer fills in the "hangman" word (user loses).

## Program Functionality

1. **Add a Sentence**: While not in a game, the user can add a sentence. Each sentence must consist of at least 1 word, and every word in the sentence must have at least 3 letters. There can be no duplicate sentences.

2. **Start the Game**: When the user starts a game, the computer selects one of the available sentences and displays it on screen, Hangman-style. This means that the computer reveals the first and last letter of every word, as well as all the occurrences of these letters within the words. The sentence selection is random.

    **Example**: For the sentence "anna has apples," the computer reveals:
    ```
    a __ a has a __ __ __ e__
    ```

3. **Play the Game**: The game consists of several rounds. In each round, the user proposes a letter. If the sentence contains the letter, the computer reveals where these letters appear within the sentence. If the sentence does not contain the letter, or if the user previously proposed the letter, the computer will add a new letter to the word "hangman," which is displayed to the user.

4. **Game Over**: The game is over when the sentence is correctly filled in (user wins), or when the computer fills in the word "hangman" (user loses).

## Non-functional Requirements

- Implement a layered architecture solution with Repository, Controller, and UI layers.
- Functionalities without tests or specification in the Repository or Controller layers will be graded at 50% value.

## Observations

- Sentences are loaded from/saved to a text file that must initially hold at least 5 entries.


## Gameplay Example

1. **Initial Display**: 
    ```
    _ _ _ _ _ _ _ _ _ _
    ```

2. **User Guess: `a`**: 
    ```
    a __ a has a __ __ __ e__
    ```

3. **User Guess: `m`**:
    ```
    a __ a has a __ __ __ e__
    ```

4. **User Guess: `n`**:
    ```
    anna has a __ __ __ e__
    ```

5. **User Guess: `x`**:
    ```
    anna has a __ __ __ e__
    - hang
    ```

6. **User Guess: `t`**:
    ```
    anna has a __ __ __ e__
    ```

7. **User Guess: `p`**:
    ```
    anna has apples
    - hang
    ```

8. **User Guess: `l`**:
    ```
    anna has apples
    - YOU WON!
    ```

In the above example, each guess updates the display or the Hangman word, leading to the end of the game with a win or loss condition.
