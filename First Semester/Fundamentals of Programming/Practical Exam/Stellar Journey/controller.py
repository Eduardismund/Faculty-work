from repo import Board


class ControllerError(Exception):
    pass


class GameOver(Exception):
    pass


class Controller:
    def __init__(self):
        self._repo = Board()

    def warp(self, x, y):
        if self._repo.to_place(x, y) == "*":
            raise ControllerError("Not possible to move over a star")
        elif self._repo.to_place(x, y) == " ":
            self._repo.move(x, y)
        elif self._repo.to_place(x, y) == "B":
            raise GameOver("Game Over!")

    def display(self):
        return self._repo