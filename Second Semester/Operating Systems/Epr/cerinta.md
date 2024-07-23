# Subject given by many teachers (Mursa in my case)

The following C program reads lowercased strings from the keyboard until 'X' is entered. The main process will start two types of child processes: A and B, each time a string is read from the keyboard.

- **Child Processes A**:
  - The parent sends the string to the created child process using pipes.
  - Each child process will initialize a vector `V` with 26 zeros and iterate over the string character by character, computing an index based on the ASCII code of the character:
    - a (97) -> 0
    - b (98) -> 1
    - c (99) -> 2
    - etc.
  - This index corresponds to a position in vector `V` that will be incremented during each character iteration.
  - This frequency vector for the characters found in the string will be sent back:
    - To the parent using pipes that will print it on the screen.
    - To process B.

- **Child Processes B**:
  - Will receive the frequency vector from the child process A with a pipe, sum up all the values, and print the result.
