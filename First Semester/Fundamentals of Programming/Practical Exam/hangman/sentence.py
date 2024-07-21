from random import randint


class RepoError(Exception):
    pass


class Sentence:
    def __init__(self):
        self._sentence = {}
        self._contor = 0
        self._normal = ''
        self._codified = ''
        self.load()

    def sentence(self):
        return self._normal, self._codified

    def load(self):
        with open("sentences.txt", "r") as file:
            for line in file:
                self._sentence[self._contor] = line.strip()
                self._contor += 1
    def set(self, sentence):
        self._codified = sentence
    def save(self):
        with open("sentences.txt", "w") as file:
            for sentence in self._sentence.values():
                file.write(sentence + "\n")

    def clean(self):
        self._normal = ''
        self._codified = ''
    def hangman(self):
        guess = randint(0, self._contor-1)
        self._normal = self._sentence[guess]
        letters = set()
        for words in self._normal.split():
            self._codified += words[0]
            letters.add(words[0])
            for char in words[1:-1]:
                self._codified = self._codified + "_"
            self._codified += words[-1]
            self._codified += " "
            letters.add(words[-1])

        letters = list(letters)
        for letter in letters:
            for i in range(len(self._normal)):
                if self._normal[i] == letter:
                    self._codified = self._codified[:i] + letter + self._codified[i + 1:]

    def add(self, sentence):
        if len(sentence.split()) < 2 or sentence in self._sentence.values():
            raise RepoError("Invalid")
        for words in sentence.split():
            if len(words) < 2:
                raise RepoError("Invalid")
        self._sentence[self._contor] = sentence
        self.save()
