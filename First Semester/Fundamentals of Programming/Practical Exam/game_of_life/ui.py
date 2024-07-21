from controller import Controller
from repo import RepoError


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()
        self._patterns = ["blinker", "tub", "beacon", "spaceship", "block"]

    def start(self):
        while True:
            try:
                print(self._controller.display())
                print("1. place a pattern")
                print("2. save to a file")
                print("3. load from a file")
                print("4. create a new generation")

                option = input(" > ")

                if option == "1":
                    print("Option of patterns:")
                    print("block")
                    print("tub")
                    print("blinker")
                    print("beacon")
                    print("spaceship")
                    pattern = input("Insert the command to place ").split()
                    if len(pattern) == 3:
                        numbers = pattern[2].split(",")
                    else:
                        raise UIError("Invalid input")

                    if len(numbers) == 2:
                        x = int(numbers[0])
                        y = int(numbers[1])
                    else:
                        raise UIError("Invalid input")
                    if len(pattern) == 3 and pattern[0] == "place" and pattern[1] in self._patterns and 1<=x<=8 and 1<=y<=8:
                        self._controller.place_pattern(pattern[1], x-1, y-1)
                    else:
                        raise UIError("Invalid input")

                elif option == "2":
                    self._controller.save_to_file()

                elif option == "3":
                    self._controller.load_from_file()

                elif option == "4":
                    command = input(" insert the number of generations: ").split()
                    if len(command) == 2 and command[0] == "tick" and command[1].isnumeric():
                        self._controller.generation(int(command[1]))
                    elif len(command) == 1 and command[0] == "tick":
                        self._controller.generation(1)
                    else:
                        raise UIError("Invalid 'tick command")


            except (RepoError, UIError) as e:
                print(e)

ui = UI()
ui.start()