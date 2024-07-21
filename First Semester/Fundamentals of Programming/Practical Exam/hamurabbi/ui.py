from repo import RepoError, GameOver
from service import Controller


class UIError(Exception):
    pass


class UI:
    def __init__(self):
        self._controller = Controller()

    def start(self):
        i = 0
        while i <= 4:
            try:
                try:
                    print(self._controller.display())
                    acres = input("Acres to buy/sell(+/-) -> ")
                    units = input("Units to feed the population -> ")
                    plant = input("Acres to plant -> ")
                    if not (acres.isnumeric() or units.isnumeric() or plant.isnumeric()):
                        raise UIError("Invalid input!")
                    self._controller.send_info(int(acres), int(units), int(plant))
                    self._controller.generate_randomness(int(units), int(plant))
                    i+=1
                    print()
                except (RepoError, UIError) as e:
                    print(e)
            except GameOver as go:
                print(go)
                break
ui = UI()
ui.start()