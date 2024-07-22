from src.domain.expense import Expense
import random


class ExpenseServices:
    def __init__(self, repo):
        self._repo = repo
        self.generate_random_values()

    def generate_random_values(self):
        """
        generates random expenses
        """
        list_of_expenses = ["Gas", "Electricity", "Telephone", "Fuel", "Insurance", "Water", "Food", "Clothes"]
        for i in range(10):
            day = random.randint(1, 30)
            amount = random.randint(1, 1000)
            type = random.choice(list_of_expenses)
            self.add_expense(day, amount, type, False)

    def add_expense(self, day, amount, type, value):
        """adds a new expense with a certain day, amount and type"""
        new_expense = Expense(day, amount, type)
        self._repo.add(new_expense, value)

    def filter_expense(self, above_value):
        """filters an expense above a certain value"""
        self._repo.filter(above_value)

    def undo_expense(self):
        """undoes the operations"""
        self._repo.undo_last_operation()
    def get_all_expenses(self):
        """returns the list of dictionary values"""
        return self._repo.get_all()