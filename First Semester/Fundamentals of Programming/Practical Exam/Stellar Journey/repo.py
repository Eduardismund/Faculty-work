import copy
from random import randint

from texttable import Texttable


class RepoError(Exception):
    pass


class Board:
    def __init__(self):
        self._board = [[' ' for _ in range(8)] for _ in range(8)]
        self.generate_stars()
        self._E = self.generate_endeavor()
        self._hidden_board = copy.deepcopy(self._board)
        self.generate_ships()

    def __str__(self):
        table = Texttable()
        letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
        table.add_row(['0'] + [str(col) for col in range(1, 9)])

        for i, row_values in enumerate(self._board):
            row_final = [letters[i]]
            line= list(row_values)
            for j in range(len(line)):
                if line[j] == "BF":
                    row_final.append(" ")
                else:
                    row_final.append(line[j])
            row_final += row_values
            table.add_row(row_final)
        return table.draw()

    def move(self, x, y):
        if x in range(self._E[0]-1, self._E[0]+2) and y in range(self._E[1]-1, self._E[1]+2) and 0 <= x <= 7 and 0 <=y <=7:
            self._board[x][y] = "E"
            self._board[self._E[0]][self._E[1]] = " "
            self._hidden_board[x][y] = "E"
            self._hidden_board[self._E[0]][self._E[1]] = " "
            self._E[0] = x
            self._E[1] = y
        else:
            raise RepoError("Not a valid move")
    def to_place(self, x, y):
        return self._hidden_board[x][y]
    def generate_ships(self):
        i = 0
        while True:
            x = randint(0, 7)
            y = randint(0, 7)
            if self._board[x][y] == " ":
                self._board[x][y] = "BF"
                i += 1
                if i == 3:
                    break
    def generate_endeavor(self):
        while True:
            x = randint(0, 7)
            y = randint(0, 7)
            if self._board[x][y] == " ":
                self._board[x][y] = "E"
                return [x, y]
    def generate_stars(self):
        i = 0
        while i < 10:
            x = randint(0, 7)
            y = randint(0, 7)
            try:
                if self._board[x+1][y] == ' ' and self._board[x-1][y] == ' ' and self._board[x][y+1] == ' ' and self._board[x][y-1] == ' ':
                    self._board[x][y] = "*"
                    i+=1
            except IndexError:
                pass

