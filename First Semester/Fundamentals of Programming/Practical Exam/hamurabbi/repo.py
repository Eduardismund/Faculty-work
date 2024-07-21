from random import randint


class RepoError(Exception):
    pass


class GameOver(Exception):
    pass


class Repo:
    def __init__(self):
        self._year = 1
        self._starved = 0
        self._city = 0
        self._population = 100
        self._land = 1000
        self._harvest = 3
        self._rats = 200
        self._land_price = 20
        self._grain = 2800

    def to_str(self):
        mes = (" In year " + str(self._year)+ ", " + str(self._starved) + " people starved.\n "
               + str(self._city) + " people came to the city. \n City population is " + str(self._population) + "\n City owns "
               + str(self._land) + " acres of land. \n Harvest was " + str(self._harvest) + " units per acre. \n Rats ate "
               + str(self._rats) + " units. \n Land price is " + str(self._land_price) + " units per acre. \n Grain stocks are: "
               + str(self._grain) + " units.")
        return mes

    def add_land(self, land_bought):
        if land_bought<=0 and land_bought *(-1)<= self._land:
            self._land += land_bought
            self._grain += land_bought * (-1) * self._land_price
        else:
            raise RepoError(" you cannot sell more land than you have!")

    def sell_land(self, land_bought):
        if land_bought >= 0 and land_bought * self._land_price <= self._grain:
            self._grain -= land_bought * self._land_price
            self._land += land_bought
        else:
            raise RepoError(" you cannot add more land than you have!")

    def feed_people_and_land(self, feed, land):
        if feed + land <= self._grain and land <= self._land:
            self._grain -= feed
            self._grain -= land
        else:
            raise RepoError(" you cannot add more land than you have!")

    def land_prices(self):
        x = randint(15, 25)
        self._land_price = x

    def starve_people(self, feed):
        starved = max(self._population - feed//20, 0)
        self._starved = starved
        self._population -= starved
        if starved > self._population//2:
            raise GameOver("You lost!")
        self._city = 0
        if starved == 0:
            x = randint(0, 10)
            self._city = x
            self._population += x

    def return_info(self):
        return self._land, self._grain
    def harvest(self, info):
        real = self._population * 10
        acres = min(real, info)
        grain = self._harvest * acres
        self._grain += grain
        x = randint(1, 6)
        self._harvest = x

    def infest(self):
        x = randint(1, 5)
        self._rats = 0
        if x == 1:
            self._rats = (10 * self._grain)//100
            self._grain -= self._rats

    def year_increase(self):
        self._year += 1
