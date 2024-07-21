from controler import Controller
from sentence import RepoError


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()
        self._hangman = "hangman"
        self._i = 0

    def play(self):
        while True:
            try:
                print("1. add a sentence:")
                print("2. play hangman")
                print("3. exit")

                option = input("> ")

                if option == "1":
                    sentence = input('insert sentence here: ')
                    self._controller.add(sentence)

                elif option == "2":
                    self._controller.start()
                    sentence = self._controller.play_hangman()
                    final = self._controller.show()

                    self.loop_hangman(sentence)

                    if self._i == 7:
                        print("YOU LOST")
                        self._controller.clean()
                        self._i = 0
                elif option == "3":
                    break

                else:
                    print("Invalid !")
            except RepoError as e:
                print(e)

    def loop_hangman(self, sentence):
        while self._i < 7:
            try:
                if self._controller.won():
                    print("YOU WON!")
                    self._controller.clean()
                    break

                print("This is the sentence coded: " + sentence)
                choice = input("choose a letter that you think is in here: ")
                if len(choice) != 1:
                    raise UIError(" I don't think so... Try again!")
                else:
                    check = self._controller.check(choice)
                    if check == True:
                        sentence = self._controller.play_hangman()
                        print(sentence)
                        print(self._hangman[0:self._i])
                    else:
                        print(sentence)
                        self._i += 1
                        print(self._hangman[0:self._i])
            except UIError as e:
                print(e)


ui = UI()
ui.play()
