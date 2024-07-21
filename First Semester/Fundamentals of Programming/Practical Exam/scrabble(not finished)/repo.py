from random import randint, shuffle


class RepoError(Exception):
    pass


class Repo:
    def __init__(self):
        self._scramble = ''
        self._word = ''
        self._data = {}
        self._letters = 0
        self._contor = 0
        self._score = 0
        self.load()
        self.random()
        self.scramble()

    def load(self):
        with open("text.txt", "r") as file:
            for line in file:
                parts = line.strip()
                self._data[self._contor] = parts
                self._contor += 1

    def random(self):
        x = randint(0, self._contor - 1)
        self._scramble = self._data[x]

    def swap(self, word1, letter1, word2, letter2):
        words = self._word.split()
        if 0 <= word1 <= len(words) and 0 <= word2 < len(words) and 1<= letter1 < len(words[word1]) and 1<= letter2 < len(words[word2]):
            words[word1] = words[word1][:letter1] + words[word2][letter2] + words[word1][letter1+1:]
            words[word2] = words[word2][:letter2] + words[word1][letter1] + words[word2][letter2 + 1:]
        else:
            raise RepoError("not good!")



    def scramble(self):
        words = self._scramble.split()
        letters = []
        for word in words:
            for i in range(len(word)):
                if i == 0 or i == len(word) - 1:
                    self._word += word[i]
                else:
                    letters.append(word[i])
                    self._word += "_"

            self._word += " "

        shuffle(letters)
        for i in range(len(self._word)):
            if self._word[i] == "_":
                self._word = self._word[:i] + letters[-1] + self._word[i + 1:]
                letters.pop()

