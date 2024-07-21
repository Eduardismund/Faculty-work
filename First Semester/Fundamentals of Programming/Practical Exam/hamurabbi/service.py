from repo import Repo


class Controller:
    def __init__(self):
        self._repo = Repo()

    def display(self):
        return self._repo.to_str()

    def send_info(self, a, b, c):
        if a < 0:
            self._repo.add_land(a)
        else:
            self._repo.sell_land(a)
        self._repo.feed_people_and_land(b, c)

    def info(self):
        return self._repo.return_info()

    def generate_randomness(self, feed, info):
        self._repo.land_prices()
        self._repo.starve_people(feed)
        self._repo.harvest(info)
        self._repo.infest()
        self._repo.year_increase()