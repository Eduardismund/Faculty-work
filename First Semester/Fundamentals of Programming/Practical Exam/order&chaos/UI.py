from board import GameOver, RepoError
from controller import Controller, ControllerError, GameWon


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()
        self._turn = 0

    def start(self):
        while True:
            try:
                print("1. continue a saved game")
                print("2. start a  new game")

                option = input(" >")

                if option == "1":
                    self._controller.retake()
                    self.play()

                elif option == "2":

                    self.play()

            except (GameOver, GameWon) as ge:
                print(ge)

    def play(self):
        while True:
            try:
                print(self._controller._display())

                if self._turn == 0:
                    move = input(" insert a X coordinate, a Y coordinate and a symbol or press file to save to file the actual game:\n").split()
                    if move[0] == "file":
                        self._controller.save()
                        self._turn = (self._turn + 1) % 2
                    if len(move) == 3 and move[2] in ["X", "O"] and 0 <= int(move[0])-1 <= 5 and 0 <= int(move[1])-1 <= 5:
                        self._controller.make_human_move(int(move[0])-1, int(move[1])-1, move[2])
                    else:
                        raise UIError("Invalid!")

                else:
                   self._controller.make_ai_move()

                self._turn = (self._turn + 1) % 2
            except (RepoError, ControllerError, UIError) as e:
                print(e)


ui = UI()
ui.start()