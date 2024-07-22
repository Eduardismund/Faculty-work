from src.services.ExpenseService import ExpenseServices

class Test:
    def __init__(self, repo):
        self._expense_services= ExpenseServices(repo)

    def test_random_values(self):
        assert len(self._expense_services.get_all_expenses()) == 10

    def test_add(self):
        self._expense_services.add_expense(10, 1000, "Parking", True)
        assert len(self._expense_services.get_all_expenses()) == 11

        self._expense_services.add_expense(20, 2000, "Vacation", True)
        assert len(self._expense_services.get_all_expenses()) == 12

    def test_filter(self):

        self._expense_services.add_expense(11, 100001, "House", True)

        self._expense_services.add_expense(11, 150000, "Surgery", True)

        self._expense_services.filter_expense(100000)

        assert len(self._expense_services.get_all_expenses()) == 2

    def test_undo(self):

        self._expense_services.undo_expense()

        assert len(self._expense_services.get_all_expenses()) == 14

        self._expense_services.undo_expense()

        assert len(self._expense_services.get_all_expenses()) == 13

        self._expense_services.undo_expense()

        assert len(self._expense_services.get_all_expenses()) == 12

    def test_all(self):
        self.test_random_values()
        self.test_add()
        self.test_filter()
        self.test_undo()