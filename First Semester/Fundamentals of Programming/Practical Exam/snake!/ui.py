from controller import Controller, GameOver


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()
        self._history = ["up"]
        self._contor = 0

    def start(self):
        while True:
            try:
                try:
                    print(self._controller._board)
                    print(self._controller.score())
                    option = input("Insert your option here:").split()
                    if len(option) == 1 and option[0] in [ "right", "left", "up", "down"]:
                        if option[0] == "right" and self._history[self._contor] != "right":
                            self._controller.right()
                            self._history.append(option[0])
                            self._contor += 1

                        if option[0] == "left" and self._history[self._contor] != "left":
                            self._controller.left()
                            self._history.append(option[0])
                            self._contor += 1
                        if option[0] == "down" and self._history[self._contor] != "down":
                            self._controller.up()
                            self._history.append(option[0])
                            self._contor += 1

                        if option[0] == "up" and self._history[self._contor] != "up":
                            self._controller.down()
                            self._history.append(option[0])
                            self._contor += 1
                        else:
                            raise UIError("YOu used that last time!")
                    elif len(option) == 2 and option[0] == "move" and option[1].isnumeric():
                        i=0
                        options = self._history[self._contor]
                        while i < int(option[1]):

                            if options == "right":
                                self._controller.right()

                            if options == "left":
                                self._controller.left()

                            if options == "down":
                                self._controller.up()

                            if options == "up":
                                self._controller.down()
                            i+=1

                    elif len(option) == 1 and option[0] == "move":
                        options = self._history[self._contor]
                        if options == "right":
                            self._controller.right()

                        if options == "left":
                            self._controller.left()

                        if options == "down":
                            self._controller.up()

                        if options == "up":
                            self._controller.down()

                    else:
                        raise UIError("Invalid format")
                except UIError as e:
                    print(e)
            except GameOver as e:
                print(e)
                break

ui = UI()
ui.start()

