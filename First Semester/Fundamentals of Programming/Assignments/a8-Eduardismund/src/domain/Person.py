class Person:
    def __init__(self, person_id: str, phone_number: str, name: str):
        self._id = person_id
        self._phone_number = phone_number
        self._name = name

    @property
    def get_id(self):
        return self._id

    @property
    def get_phone_number(self):
        return self._phone_number

    @property
    def get_name(self):
        return self._name

    def __str__(self):
        return "Name Id: "+ self._id + " | "+ "Name: "+ self._name + " | " + "Phone Number: " + self._phone_number