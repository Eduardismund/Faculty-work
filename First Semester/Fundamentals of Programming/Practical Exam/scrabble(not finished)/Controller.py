from repo import Repo


class Controller:
    def __init__(self):
        self._repo = Repo()

    def swap(self, a, b, c, d):
        self._repo.swap(a,b,c,d)

    def show_score(self):
        return self._repo._score

    def show_sentence(self):
        return self._repo._word