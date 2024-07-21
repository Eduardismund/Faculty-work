from controller import Controller, ControllerError, GameOver
from repo import RepoError


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()
        self._letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']

    def start(self):
        while True:
            try:
                try:
                    print(self._controller.display())
                    print("Give a command: warp <coordinate>, fire <coordinate> or cheat")

                    option = input("> ").split()

                    if len(option) == 2:
                        x, y = self.check_input(option)

                        if option[0] == "warp":
                            self._controller.warp(x,y)

                    if len(option) == 1 and option == "cheat":
                        pass

                except (ControllerError, RepoError, UIError) as e:
                    print(e)
            except GameOver as e:
                print(e)
                break

    def check_input(self, option):
        x = 10
        if len(option[1])==2 and option[1][0] in self._letters and option[1][1].isnumeric():
            for i in range(len(self._letters)):
                if self._letters[i] == option[1][0]:
                    x = i

            if x == 10:
                raise UIError("Not a good coordinate!")
        else:
            raise UIError("Not a good coordinate!")

        if int(option[1][1]) - 1 in range(0, 8):
            y = int(option[1][1]) - 1
        else:
            raise UIError("Not a good coordinate!")

        return x, y

ui = UI()
ui.start()