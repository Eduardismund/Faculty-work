from Controller import Controller
from repo import RepoError


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()

    def start(self):
        while True:
            try:

                self._controller.show_score()
                print("1. swap 2 letters between words")
                option = input("> ")

                if option == "1":
                    command = input("Insert the command to swap").split()
                    if len(command) == 6 and command[0] == "swap" and command[3] == "-":
                        self._controller.swap(int(command[1]), int(command[2]), int(command[4]), int(command[5]))
                    else:
                        raise UIError("INvalid!")
                    print(self._controller.show_sentence())
            except (RepoError, UIError) as e:
                print(e)



ui = UI()
ui.start()