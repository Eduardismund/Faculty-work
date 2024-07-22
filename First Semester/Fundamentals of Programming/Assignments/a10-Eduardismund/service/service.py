from random import randint

from domain.board import BoardError


class GomokuService:
    def __init__(self, board):
        """
        Initialize GomokuService with the specified Gomoku board.

        :param board: Gomoku board object.
        """
        self.board = board
        self.current_player = 'X'

    def make_player_move(self, row, col):
        """
        Make a move on the Gomoku board for the current player.

        :param row: Row index for the move.
        :param col: Column index for the move.
        :return: True if the move is successful.
        :raises BoardError: If the move is invalid.
        """
        try:
            self.board.valid_move(row, col)
            self.board.make_move(self.current_player, row, col)
            return True
        except BoardError as e:
            raise e

    def make_ai_move(self):
        """
        Make a move for the AI player.

        :return: Tuple (row, col) representing the AI's move.
        """
        for i in range(15):
            for j in range(15):
                try:
                    if self.board.valid_move(i, j):
                        self.board.make_move('O', i, j)
                        if self.board.check_win('O', i, j):
                            return i, j
                        else:
                            self.board.remove_move(i, j)
                except BoardError:
                    pass

        for i in range(15):
            for j in range(15):
                try:
                    if self.board.valid_move(i, j):
                        self.board.make_move('X', i, j)
                        if self.board.check_win('X', i, j):
                            self.board.make_move('O', i, j)
                            return i, j
                        else:
                            self.board.remove_move(i, j)
                except BoardError:
                    pass

        return self.strategy_to_place()

    def get_player_at(self, row, col):
        return self.board.get_player(row, col)

    def strategy_to_place(self):
        """
        Choose a random strategy to place a move for the AI.

        :return: Tuple (row, col) representing the AI's move.
        """
        while True:
            x = randint(0, 14)
            y = randint(0, 14)
            try:
                if self.board.valid_move(x, y):
                    self.board.make_move('O', x, y)
                    return x, y
            except BoardError:
                pass

    def clear_table(self):
        """
        Clear the Gomoku board to start a new game.
        """
        self.board.reset_board()

    def check_winner(self, player, row, column):
        """
        Check if a player has won the game.

        :param player: Player to check for a win.
        :param row: Row index for the last move.
        :param column: Column index for the last move.
        :return: True if the player has won.
        """
        return self.board.check_win(player, row, column)

    def to_display(self):
        """
        Display the current state of the Gomoku board.
        """



        table = self.board.display()
        return table

    def check_is_draw(self):
        self.board.is_draw()
