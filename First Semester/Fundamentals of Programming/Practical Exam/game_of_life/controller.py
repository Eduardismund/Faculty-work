from repo import Repo


class Controller:
    def __init__(self):
        self._repo = Repo()

    def display(self):
        return self._repo

    def place_pattern(self, pattern, x, y):
        self._repo.load(pattern)
        self._repo.place_pattern(x, y)

    def load_from_file(self):
        self._repo.load_from_file()

    def save_to_file(self):
        self._repo.save_to_file()

    def generation(self, number):
        while number > 0:
            self._repo.generation()
            number -= 1