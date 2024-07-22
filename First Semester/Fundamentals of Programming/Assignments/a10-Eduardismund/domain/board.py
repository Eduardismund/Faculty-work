from prettytable import PrettyTable


class BoardError(Exception):
    pass


class Board:
    def __init__(self, size=15):
        """
        Initialize the Gomoku board.

        :param size: Size of the board (default is 15x15).
        """
        self._size = size
        self._board = [[' ' for _ in range(size)] for _ in range(size)]
        self._counter = 0

    def display(self):
        """
        Display the current state of the Gomoku board.
        """
        table = PrettyTable(field_names=[], header=False)
        for row in self._board:
            table.add_row(row)
        return table

    def make_move(self, player, row, col):
        """
        Make a move on the Gomoku board.

        :param player: Player making the move ('X' or 'O').
        :param row: Row index for the move.
        :param col: Column index for the move.
        """
        self._board[row][col] = player
        self._counter += 1

    def get_player(self, row, col):
        return self._board[row][col]

    def valid_move(self, row, col):
        """
        Check if a move is valid on the Gomoku board.

        :param row: Row index for the move.
        :param col: Column index for the move.
        :raises BoardError: If the move is invalid.
        :return: True if the move is valid.
        """
        if not (0 <= row <= 14 and 0 <= col <= 14):
            raise BoardError("Invalid input")
        if self._board[row][col] != " ":
            raise BoardError("Already taken")
        return True

    def is_draw(self):
        """
        Check if the game is a draw.

        :raises BoardError: If the game is a draw.
        """
        if self._counter == 15 * 15:
            raise BoardError("Oh no! It is a draw!")

    def check_win(self, player, row, column):
        """
        Check if a player has won the game.

        :param player: Player to check for a win.
        :param row: Row index for the last move.
        :param column: Column index for the last move.
        :return: True if the player has won.
        """
        minn = max(0, column - 5)
        maxx = min(14, column + 5)
        consecutive_count = 0
        for c in range(minn, maxx + 1):
            if self._board[row][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0

        minn = max(0, row - 5)
        maxx = min(14, row + 5)
        consecutive_count = 0
        for r in range(minn, maxx + 1):
            if self._board[r][column] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0

        consecutive_count = 0
        for i in range(-5, 6):
            r, c = row + i, column + i
            if 0 <= r < 15 and 0 <= c < 15 and self._board[r][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0

        consecutive_count = 0
        for i in range(-5, 6):
            r, c = row - i, column + i
            if 0 <= r < 15 and 0 <= c < 15 and self._board[r][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0
        return False

    def reset_board(self):
        """
        Reset the Gomoku board to its initial state.
        """
        self._board = [[' ' for _ in range(self._size)] for _ in range(self._size)]
        self._counter = 0

    def remove_move(self, row, col):
        """
        Remove a move from the Gomoku board.

        :param row: Row index of the move to be removed.
        :param col: Column index of the move to be removed.
        """
        self._board[row][col] = ' '
