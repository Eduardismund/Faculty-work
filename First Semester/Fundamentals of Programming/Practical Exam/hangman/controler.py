from sentence import Sentence


class Controller:
    def __init__(self):
        self._repo = Sentence()

    def add(self, sentence):
        self._repo.add(sentence)

    def won(self):
        if self._repo._normal == self._repo._codified[0:-1]:
            return True
        else:
            return False
    def check(self, letter):
        ok = 0
        sentence, codified = self._repo.sentence()
        for old_letter in range(len(sentence)):
            if sentence[old_letter] == letter:
                codified = codified[:old_letter] + letter + codified[old_letter+1:]
                ok = 1

        if ok == 1:
            self._repo.set(codified)
            return True
        else:
            return False
    def clean(self):
        self._repo.clean()
    def show(self):
        return self._repo._normal
    def play_hangman(self):
        return self._repo._codified

    def start(self):
        self._repo.hangman()