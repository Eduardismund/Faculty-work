from copy import deepcopy

from texttable import Texttable


class RepoError(Exception):
    pass


class Repo:
    def __init__(self):
        self._data = [[ " " for _ in range(8)] for _ in range(8)]
        self._model = ''

    def __str__(self):
        table = Texttable()

        for line in self._data:
            table.add_row(line)

        return table.draw()

    def place_pattern(self, x, y):
        board = self._data
        l = len(self._model)
        for i in range(l):
            for j in range(l):
                try:
                    if board[x+i][y+j] != " ":
                        raise RepoError("Cannot place it here!")
                    else:
                        board[x+i][j+y] = self._model[i][j]
                except IndexError:
                    raise RepoError("Cannot place it here!")

        self._data = board


    def load_from_file(self):
        i = 0
        with open("game.txt", "r") as file:
            for line in file:
                parts = line.strip().split(",")
                for j in range(len(parts)-1):
                    if parts[j] != "+":
                        self._data[i][j] = parts[j]
                    else:
                        self._data[i][j] = " "
                i+=1

    def generation(self):
        copy = deepcopy(self._data)

        for i in range(8):
            for j in range(8):
                n= 0
                try:
                    if self._data[i-1][j] == "X":
                        n+=1
                except IndexError:
                    pass

                try:
                    if self._data[i-1][j-1] == "X":
                        n+=1
                except IndexError:
                    pass

                try:
                    if self._data[i-1][j+1] == "X":
                        n+=1
                except IndexError:
                    pass

                try:
                    if self._data[i][j+1] == "X":
                        n+=1
                except IndexError:
                    pass
                try:
                    if self._data[i][j-1] == "X":
                        n+=1
                except IndexError:
                    pass

                try:
                    if self._data[i+1][j] == "X":
                        n+=1
                except IndexError:
                    pass

                try:
                    if self._data[i+1][j-1] == "X":
                        n+=1
                except IndexError:
                    pass
                try:
                    if self._data[i+1][j+1] == "X":
                        n+=1
                except IndexError:
                    pass
                if n < 2 and self._data[i][j] == "X":
                    copy[i][j] = ' '
                elif (n == 2 or n == 3) and self._data[i][j] == "X":
                    copy[i][j] = 'X'
                elif n > 3 and self._data[i][j] == "X":
                    copy[i][j] = ' '
                elif n == 3 and self._data[i][j] == " ":
                    copy[i][j] = 'X'
                else:
                    copy[i][j] = ' '
        self._data = copy



    def save_to_file(self):
        with open("game.txt", "w") as file:
            for i in range(8):
                line = ''
                for j in range(8):
                    if self._data[i][j] == " ":
                        line += "+"
                    else:
                        line += str(self._data[i][j])
                    line+=','
                line+="\n"
                file.write(line)

    def load(self, name):
        model = []
        ok = 0
        with open("file.txt", "r") as file:
            for line in file:
                if line.strip() == name:
                    ok = 1
                    i=0
                elif ok == 1 and (line.strip()[0] == 'x' or line.strip()[0] == '+') :
                    parts=line.strip().split(',')
                    if len(model) <= i:
                        model.append([])
                    for j in range(len(parts)):
                        if parts[j] == '+':
                            model[i].append(' ')
                        else:
                            model[i].append('X')
                    i+=1
                elif ok == 1 and line.strip().isalpha():
                    break
        self._model = model




