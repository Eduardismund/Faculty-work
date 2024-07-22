import _pickle

from src.repository.MemoryRepository import MemoryRepository
from src.domain.expense import Expense
import pickle

class BinaryFileRepository(MemoryRepository):
    """
    data saved in 'expenses.bin' and inherits all the methods and functions from MemoryRepository
    """
    def __init__(self, file_name="expenses.bin"):
        """
        inherits the necessary methods and in addition it requires a file to which we load from
        """
        super(BinaryFileRepository, self).__init__()
        self._file_name = file_name
        self._load_from_file()

    def _load_from_file(self):
        """
        if there is something to load, it will do so and add it
        """
        try:
            fin = open(self._file_name, 'rb')
            obj= pickle.load(fin)
        except EOFError:
            return

        for new_expense in obj:
            super().add(new_expense,False)
        fin.close()

    def save_at_file(self):
        """saves the data by writing it in the file"""
        fout = open(self._file_name, "wb")
        pickle.dump(self.get_all(),fout)
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
