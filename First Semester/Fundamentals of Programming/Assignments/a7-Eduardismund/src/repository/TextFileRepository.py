from src.repository.MemoryRepository import MemoryRepository
from src.domain.expense import Expense

class TextFileRepository(MemoryRepository):
    """
    data saved in 'expenses.txt' and inherits all the methods and functions from MemoryRepository
    """
    def __init__(self, file_name="expenses.txt"):
        """
            inherits the necessary methods and in addition it requires a file to which we load from
        """
        super(TextFileRepository, self).__init__()
        self._file_name = file_name
        self._load_from_file()

    def _load_from_file(self):
        """opens the text file from which lines are read and split into day, amount and expense,
         a new expense being created afterward"""

        read=[]

        try:
            fin = open(self._file_name, 'rt')
            read=fin.readlines()
            fin.close()
        except IOError:
            pass

        for to_read in read:
            line=to_read.split(",")
            new_expense = Expense(int(line[0].strip()), int(line[1].strip()), line[2].strip())
            super().add(new_expense,False)

    def save_at_file(self):

        """
        writes the data back into the file
        """
        fout = open(self._file_name, "wt")

        for expense in self.get_all():
            expense_list=str(expense.day)+','+str(expense.amount)+','+expense.type+"\n"
            fout.write(expense_list)

        fout.close()


    def add(self, new_expense, value):
        """
        inherited and the same as in memoryRepository
        """
        super().add(new_expense, value)
        self.save_at_file()

    def filter(self, above_value):
        """
        inherited and the same as in memoryRepository
        """
        super().filter(above_value)
        self.save_at_file()

    def undo_last_operation(self):
        """
        inherited and the same as in memoryRepository
        """
        super().undo_last_operation()
        self.save_at_file()
