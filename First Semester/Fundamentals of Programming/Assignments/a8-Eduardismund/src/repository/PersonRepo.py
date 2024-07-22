from src.domain.Person import Person


class RepoError(Exception):
    """
    The exception raised in the class below
    """
    pass
class PersonRepo:
    """
    Class that manages the persons
    """
    def __init__(self):
        self._data={}
        self._id_list=[]

    def add(self, new_person : Person):
        """
        adding a person if the id is not already in use, else raising an error
        """
        if new_person._id not in self._data:
            self._data[new_person._id] = new_person
            self._id_list.append(new_person.get_id)
        else:
            raise RepoError
    def get_list(self):
        """
        returns the list of all ID's uniquely generated
        """
        return self._id_list
    def get_person(self, id):
        """
        checks whether a person's ID is found in the list or not
        """
        if id in self._data:
            return self._data[id]
        else:
            return "Not an existing person"

    def remove(self, person_id):
        """removes a person if found in the list otherwise raises an Error either by not having the id to delete or
        by reaching the end of the dictionary"""
        if self._data=={}:
            raise RepoError("Nothing to remove here!\n")
        if person_id in self._data:
            del self._data[person_id]
        else:
            raise RepoError("Cannot remove an ID not in use.\n")

    def update(self, person_id, new_person):
        """
        updates an old person id with a new one, if there is nothing to update or the id doesnt exist, an error will be raised
        """
        if self._data=={}:
            raise RepoError("Nothing to update here!")
        if person_id in self._data:
            self._data[person_id] = new_person
        else:
            raise RepoError("Cannot update an ID not in use.\n")

    def search_after_phone_number(self, phone_number):
        """
        searches a phone number in the dictionary and returns any occurrence that is partial or a complete match
        """
        occurrences=[]
        for obj in self._data.values():
            if phone_number in obj._phone_number:
                occurrences.append(obj)
        return occurrences

    def search_after_name(self, name):
        """
            searches a name in the dictionary and returns any occurrence that is partial or a complete match
        """
        occurrences=[]
        name=name.lower()
        for obj in self._data.values():
            obj_name=obj._name.lower()
            if name in obj_name:
                occurrences.append(obj)
        return occurrences

    def get_all(self):
        """
        :return: all the values from the dictionary, the people data
        """
        return list(self._data.values())