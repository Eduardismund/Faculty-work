from random import randint

from texttable import Texttable


class Board:
    def __init__(self):
        self._n, self._apples = self.load()
        self._board = [[' ' for _ in range(self._n)] for _ in range(self._n)]
        self._gone = []
        self._contor = 0
        self._x = self._n // 2
        self._y = self._n // 2
        self.place_snake()
        self.place_apple(0)


    def load(self):
        with open("snake.txt", "r") as file:
            for line in file:
                parts = line.split()
                return int(parts[2]), int(parts[6])

    def __str__(self):
        table = Texttable()
        for row in self._board:
            table.add_row(row)

        return table.draw()

    def place_snake(self):
        self._board[self._n // 2][self._n // 2] = '*'
        self._board[(self._n // 2) + 1][self._n // 2] = '+'
        self._board[(self._n // 2) + 2][self._n // 2] = '+'
        self._gone.append(((self._n // 2) + 2, self._n // 2))
        self._gone.append(((self._n // 2) + 1, self._n // 2))
        self._gone.append(((self._n // 2), self._n // 2))

    def place_apple(self, i):
        while i < self._apples:
            x = randint(1, self._n - 2)
            y = randint(1, self._n - 2)
            try:
                if self._board[x][y] == ' ' and self._board[x][y+1] !='a' and self._board[x-1][y] !='a' and self._board[x+1][y] !='a' and self._board[x][y-1] !='a':
                    self._board[x][y] = 'a'
                    i += 1
            except IndexError:
                pass

    def move_right(self):
        return self._board[self._x][self._y+1]

    def move_up(self):
        return self._board[self._x+1][self._y]

    def move_down(self):
        return self._board[self._x-1][self._y]

    def move_left(self):
        return self._board[self._x][self._y-1]

    def good_right(self):
        self._board[self._x][self._y + 1] = "*"
        self._board[self._x][self._y] = "+"
        self._y += 1

    def good_up(self):
        self._board[self._x+1][self._y] = "*"
        self._board[self._x][self._y] = "+"
        self._x += 1

    def good_down(self):
        self._board[self._x-1][self._y] = "*"
        self._board[self._x][self._y] = "+"
        self._x -= 1

    def good_left(self):
        self._board[self._x][self._y - 1] = "*"
        self._board[self._x][self._y] = "+"
        self._y -= 1

    def clean(self):
        x, y = self._gone[self._contor]
        self._board[x][y] = ' '
        self._contor += 1
        self._gone.append((self._x, self._y))

    def reminder(self):
        self._gone.append((self._x, self._y))