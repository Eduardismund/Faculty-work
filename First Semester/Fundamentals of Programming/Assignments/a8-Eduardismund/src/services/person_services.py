from random import choice
from src.domain.Person import Person
from src.repository.PersonRepo import PersonRepo, RepoError
from src.services.activity_services import ServiceError


class Person_services:
    """
    handles people services
    """
    def __init__(self, list_of_numbers):
        """
        Constructor having the PersonREpo and calls the function to generate 20 people at start-up
        """
        self.__repo=PersonRepo()
        self.generate_random_numbers(list_of_numbers)

    def generate_random_numbers(self, list_of_numbers):
        """
        The 20 people generated at start-up, having the name, id, and phone number randomly generated
        """
        list_of_names=['Alex', 'Delia', 'Ioana', 'Eduard', 'Mihai', 'Ariana', 'Aris', 'Tudor', 'Eric', 'Lucian', 'Luca', 'Xenia', 'Mike', 'Sonia', 'Romeo', 'Rumulus', 'Andreea', 'Emanuel', 'Mark', 'Constantin', 'Dania', 'Iustina', 'Nikol']
        mobile_prefix="07"
        for i in range(20):
            name=choice(list_of_names)
            id=str(list_of_numbers[i])
            number=''.join(choice("0123456789") for _ in range(8))
            pn=mobile_prefix+number
            self.add_person(id, pn, name)

    def get_personn(self, id):
        """
        returns the person having a certain id from the dictionary
        """
        return self.__repo.get_person(id)

    def add_person(self, id, phone_number, name):
        """
        creates a person with input data from the ui and creates a new person that should be added to the repo if the validity
        protocols are checked
        """
        new_person = Person(id, phone_number, name)
        try:
            self.__repo.add(new_person)
        except RepoError:
            raise ServiceError("Cannot Add")

    def remove_person(self, id):
        """
        removes a person using the id, input data from the ui if the validity protocol is validated successfully
        """
        try:
            self.__repo.remove(id)
        except RepoError:
            raise ServiceError("Cannot remove")

    def update_person(self, old_id, new_id, phone_number, name):
        """
        updates a person having a certain index, with new input data from the ui if the validity protocol is validated successfully
        """
        new_person = Person(new_id, phone_number, name)
        try:
            self.__repo.update(old_id, new_person)
        except RepoError:
            raise ServiceError("Cannot update")

    def get_all_persons(self):
        """
        returns all the persons from the repo
        """
        return self.__repo.get_all()

    def get_listt(self):
        """
        returns the list of active ID's in the current state
        """
        return self.__repo.get_list()

    def search_person_based_on_phone_number(self, phone_number):
        """
            searches a phone_number in the dictionary(sending it to repo) and returns any occurrence that is partial or a complete match
        """
        return self.__repo.search_after_phone_number(phone_number)

    def search_person_based_on_name(self, name):
        """
            searches a name in the dictionary(sending it to repo) and returns any occurrence that is partial or a complete match
        """
        return self.__repo.search_after_name(name)