from src.repository.PersonRepo import PersonRepo
import pickle


class PersonRepoBinaryFile(PersonRepo):
    """
    data saved in 'expenses.bin' and inherits all the methods and functions from MemoryRepository
    """

    def __init__(self, file_name="person.bin"):
        """
        inherits the necessary methods and in addition it requires a file to which we load from
        """
        super(PersonRepoBinaryFile, self).__init__()
        self._file_name = file_name
        self._load_from_file()

    def _load_from_file(self):
        """
        if there is something to load, it will do so and add it
        """
        try:
            fin = open(self._file_name, 'rb')
            obj = pickle.load(fin)
        except EOFError:
            return

        for new_person in obj:
            super().add(new_person)
        fin.close()

    def save_at_file(self):
        """saves the data by writing it in the file"""
        fout = open(self._file_name, "wb")
        pickle.dump(self.get_all(), fout)
        fout.close()

    def add(self, new_person):
        """
        inherited and the same as in memoryRepository
        """
        super().add(new_person)
        self.save_at_file()

    def update(self, old_id, new_person):
        """
            inherited and the same as in memoryRepository
        """
        super().update(old_id, new_person)
        self.save_at_file()

    def remove(self, person_id):
        """
        inherited and the same as in memoryRepository
        """
        super().remove(person_id)
        self.save_at_file()
