from random import randint, choice

from texttable import Texttable


class RepoError(Exception):
    pass


class GameOver(Exception):
    pass


class Board:
    def __init__(self):
        self._board = [[' ' for _ in range(6)] for _ in range(6)]
        self._contor = 0

    def __str__(self):
        table = Texttable()

        for row in self._board:
            table.add_row(row)

        return table.draw()

    def lost(self):
        if self._contor == 35:
            raise GameOver(" YOU LOST!")

    def save_to_file(self):
        with open("text.txt", "w") as file:
            line = ''
            for i in range(6):
                for j in range(6):
                    if self._board[i][j] == " ":
                        line += "+ "
                    else:
                        line += str(self._board[i][j])
                        line += " "
                line = line+ "\n"
                file.write(line)
                line = ""

    def load(self):
        with open("text.txt", "r") as file:
            j = 0
            for line in file:
                parts = line.strip().split()
                for i in range(len(parts)):
                    if parts[i] == "+":
                        self._board[j][i] = " "
                    else:
                        self._board[j][i] = parts[i]
                j+=1

    def contor(self):
        return self._contor

    def dec(self):
        self._contor -= 1

    def make_move(self, X, Y, symbol):
        if 0 <= X <= 5 and 0 <= Y <= 5 and self._board[X][Y] == " ":
            self._board[X][Y] = symbol
            self._contor += 1
        else:
            raise RepoError("not valid move!")

    def valid_move(self, x, y):
        if 0 <= x <= 5 and 0 <= y <= 5:
            return True
        else:
            return False

    def remove_move(self, x, y):
        self._board[x][y] = " "

    def check_win(self, player, row, column):
        """
        Check if a player has won the game.

        :param player: Player to check for a win.
        :param row: Row index for the last move.
        :param column: Column index for the last move.
        :return: True if the player has won.
        """
        minn = max(0, column - 5)
        maxx = min(5, column + 5)
        consecutive_count = 0
        for c in range(minn, maxx + 1):
            if self._board[row][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0

        minn = max(0, row - 5)
        maxx = min(5, row + 5)
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
            if 0 <= r < 6 and 0 <= c < 6 and self._board[r][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0

        consecutive_count = 0
        for i in range(-5, 6):
            r, c = row - i, column + i
            if 0 <= r < 6 and 0 <= c < 6 and self._board[r][c] == player:
                consecutive_count += 1
                if consecutive_count == 5:
                    return True
            else:
                consecutive_count = 0
        return False

    def strategy_to_place(self):
        while True:
            x = randint(0, 5)
            y = randint(0, 5)
            symbol = choice(["X", "O"])
            if self._board[x][y] == " ":
                self.make_move(x, y, symbol)
                break


