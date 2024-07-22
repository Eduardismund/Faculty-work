from src.domain.Person import Person
from src.repository.PersonRepo import PersonRepo


class PersonRepoTextFile(PersonRepo):
    """
    data saved in 'expenses.txt' and inherits all the methods and functions from MemoryRepository
    """

    def __init__(self, file_name="person.txt"):
        """
            inherits the necessary methods and in addition it requires a file to which we load from
        """
        super(PersonRepoTextFile, self).__init__()
        self._file_name = file_name
        self._load_from_file()

    def _load_from_file(self):
        """opens the text file from which lines are read and split into day, amount and expense,
         a new expense being created afterward"""

        read = []

        try:
            fin = open(self._file_name, 'rt')
            read = fin.readlines()
            fin.close()
        except IOError:
            pass

        for to_read in read:
            line = to_read.split(",")
            new_person = Person(line[0].strip(), line[1].strip(), line[2].strip())
            super().add(new_person)

    def save_at_file(self):

        """
        writes the data back into the file
        """
        fout = open(self._file_name, "wt")

        for person in self.get_all():
            person_list = person._id + ',' + person._phone_number + ',' + person._name + "\n"
            fout.write(person_list)

        fout.close()

    def add(self, new_person):
        """
        inherited and the same as in memoryRepository
        """
        super().add(new_person)
        self.save_at_file()

    def remove(self, person_id):
        """
        inherited and the same as in memoryRepository
        """
        super().remove(person_id)
        self.save_at_file()

    def update(self, person_id, new_person):
        """
        inherited and the same as in memoryRepository
        """
        super().update(person_id, new_person)
        self.save_at_file()
