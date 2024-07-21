from board import Board, RepoError


class ControllerError(Exception):
    pass


class GameWon(Exception):
    pass


class Controller:
    def __init__(self):
        self._board = Board()

    def _display(self):
        return self._board

    def coordinates(self, x, y):
        return self._board._board[x][y]

    def save(self):
        self._board.save_to_file()
    def retake(self):
        self._board.load()
    def make_human_move(self, x, y, symbol):
        self._board.make_move(x, y, symbol)
        if self._board.check_win(symbol, x, y):
            raise GameWon("You won!")

    def contor(self):
        return self._board.contor()

    def make_ai_move(self):
        for i in range(6):
            for j in range(6):
                try:
                    if self._board.valid_move(i, j):
                        self._board.make_move( i, j, "O")
                        self._board.dec()
                        if self._board.check_win('O', i, j):
                            self._board.remove_move(i, j)
                            self._board.make_move(i, j, 'X')
                            if self._board.check_win("X", i, j):
                                raise ControllerError("You won!")
                            return
                        else:
                            self._board.remove_move(i, j)
                except RepoError:
                    pass

        for i in range(6):
            for j in range(6):
                try:
                    if self._board.valid_move(i, j):
                        self._board.make_move( i, j, 'X')
                        self._board.dec()
                        if self._board.check_win('X', i, j):
                            self._board.remove_move(i, j)
                            self._board.make_move(i, j, 'O')
                            if self._board.check_win("O", i, j):
                                raise ControllerError("You won!")
                            return
                        else:
                            self._board.remove_move(i, j)
                except RepoError:
                    pass
        self._board.strategy_to_place()
        return

