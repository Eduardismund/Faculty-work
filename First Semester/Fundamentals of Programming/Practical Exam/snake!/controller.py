from repo import Board


class GameOver(Exception):
    pass


class Controller:
    def __init__(self):
        self._board = Board()
        self._score = 0

    def right(self):
        try:
            if self._board.move_right() == "+":
                raise GameOver("You lost!")

            elif self._board.move_right() == "a":
                self._board.good_right()
                self._score += 1
                apple = self._board._apples
                self._board.place_apple(apple-1)
                self._board.reminder()
            else:
                self._board.good_right()
                self._board.clean()
        except IndexError:
            raise GameOver("You lost!")

    def left(self):
        try:
            if self._board.move_left() == "+":
                raise GameOver("You lost!")
            elif self._board.move_left() == "a":
                self._board.good_left()
                self._score += 1
                apple = self._board._apples
                self._board.place_apple(apple - 1)
                self._board.reminder()
            else:
                self._board.good_left()
                self._board.clean()
        except IndexError:
            raise GameOver("You lost!")

    def up(self):
        try:
            if self._board.move_up() == "+":
                raise GameOver("You lost!")
            elif self._board.move_up() == "a":
                self._board.good_up()
                self._score += 1
                apple = self._board._apples
                self._board.place_apple(apple - 1)
                self._board.reminder()
            else:
                self._board.good_up()
                self._board.clean()
        except IndexError:
            raise GameOver("You lost!")

    def down(self):
        try:
            if self._board.move_down() == "+":
                raise GameOver("You lost!")
            elif self._board.move_down() == "a":
                self._board.good_down()
                self._score += 1
                apple = self._board._apples
                self._board.place_apple(apple - 1)
                self._board.reminder()
            else:
                self._board.good_down()
                self._board.clean()
        except IndexError:
            raise GameOver("You lost!")

    def score(self):
        return self._score
