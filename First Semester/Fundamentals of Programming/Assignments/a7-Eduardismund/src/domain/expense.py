from dataclasses import dataclass
@dataclass
class Expense:

    def __init__(self, day, amount, type):
        """an expense is defined as a combination of day, amount and type"""
        self.day = day
        self.amount = amount
        self.type = type

    @property
    def get_day(self):
        """manipulates the day"""
        return self.day

    @property
    def get_amount(self):
        """manipulates the amount"""
        return self.amount

    @property
    def get_type(self):
        """manipulates the type"""
        return self.type

    def __str__(self):
        """printing it"""
        return "day: "+ str(self.day) + " | " + "amount: "+ str(self.amount) + " | " + "type: " +self.type