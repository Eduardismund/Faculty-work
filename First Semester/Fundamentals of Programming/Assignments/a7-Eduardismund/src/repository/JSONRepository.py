import json
import os
from src.domain.expense import Expense
from src.repository.MemoryRepository import MemoryRepository


class JSONRepository(MemoryRepository):
    """
        data saved in 'expenses.json' and inherits all the methods and functions from MemoryRepository
    """
    def __init__(self, file_name="expenses.json"):
        super(JSONRepository, self).__init__()
        self._file_name = file_name
        self._init_file()
        self._load_file()

    def reset_file(self):
        fout = open(self._file_name, "w")
        fout.write("{}")
        fout.close()

    def _init_file(self):
        filesize = os.path.getsize(self._file_name)
        if filesize == 0:
            self.reset_file()

    def _load_file(self):
        """
        Loads the expenses from a json file
        """
        data = {}

        try:
            fin = open(self._file_name)
            data = json.load(fin)
            fin.close()
        except IOError:
            pass

        for exp in data:
            new_expense = Expense(exp["day"], exp["amount"],
                                  exp["type"])
            super().add(new_expense, False)

    def save_at_file(self):
        """
        Saves all expenses to our json file
        """
        expenses = []

        fout = open(self._file_name, "w")

        for exp in self.get_all():
            expenses.append(exp.__dict__)

        json.dump(expenses, fout, indent=1)

        fout.close()

    def add(self, new_expense, value):
        super().add(new_expense, value)
        self.save_at_file()

    def filter(self, above_value):
        super().filter(above_value)
        self.save_at_file()

    def undo_last_operation(self):
        super().undo_last_operation()
        self.save_at_file()
