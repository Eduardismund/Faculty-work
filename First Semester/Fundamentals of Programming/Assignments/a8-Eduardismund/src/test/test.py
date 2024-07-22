import unittest
from datetime import datetime
from random import randint
from src.services.activity_services import Activity_services, ServiceError
from src.services.person_services import Person_services

def generate_unique_numbers(num_numbers, start_range, end_range):
    unique_numbers = set()

    while len(unique_numbers) < num_numbers:
        random_number = randint(start_range, end_range)
        unique_numbers.add(random_number)

    return list(unique_numbers)


class TestPeople(unittest.TestCase):
    def test_generate_random_values_people(self):
        list_of_numbers=generate_unique_numbers(20,100,999)
        list_people = Person_services(list_of_numbers)
        self.assertEqual(len(list_people.get_all_persons()), 20, "oops")


    def test_add(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        name = "Helen"
        phone_number="0783040506"
        list_people = Person_services(list_of_numbers)
        list_people.add_person(id, phone_number, name)
        self.assertEqual(len(list_people.get_all_persons()), 21)

    def test_add_duplicate(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        name = "Helen"
        phone_number="0783040506"
        list_people = Person_services(list_of_numbers)
        list_people.add_person(id, phone_number, name)
        with self.assertRaises(ServiceError): list_people.add_person(id, phone_number, name)

    def test_update(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        name = "Helen"
        phone_number = "0783040506"
        list_people = Person_services(list_of_numbers)
        list_people.add_person(id, phone_number, name)
        id2="98"
        name2="Miruna"
        phone_number2="0778043576"
        list_people.update_person(id,id2, phone_number2, name2)
        self.assertEqual(len(list_people.get_all_persons()), 21)

    def test_update_duplicate(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        name = "Helen"
        phone_number = "0783040506"
        list_people = Person_services(list_of_numbers)
        with self.assertRaises(ServiceError): list_people.update_person('-100',id, phone_number, name)

    def test_remove(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        name = "Helen"
        phone_number = "0783040506"
        list_people = Person_services(list_of_numbers)
        list_people.add_person(id, phone_number, name)
        list_people.remove_person(id)
        self.assertEqual(len(list_people.get_all_persons()), 20)

class TestActivity(unittest.TestCase):
    def test_generate_random_values_activity(self):
        list_of_numbers=generate_unique_numbers(20,100,999)
        list_activities = Activity_services(list_of_numbers)
        self.assertEqual(len(list_activities.get_all_activities()), 20, "oops")

    def test_add(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        date=datetime(2022, 12, 12,12,00,00)
        time= "10:00:00"
        desc="cooking"
        people=Person_services(list_of_numbers)
        people_id=people.get_listt()
        list_activities = Activity_services(list_of_numbers)
        list_activities.add_activity(id, str(people_id[1]), date, time, desc,[])
        self.assertEqual(len(list_activities.get_all_activities()), 21)

    def test_add_duplicate(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "98"
        date = datetime(2022, 12, 12, 12, 00, 00)
        time = "10:00:00"
        desc = "cooking"
        people = Person_services(list_of_numbers)
        people_id = people.get_listt()
        list_activities = Activity_services(list_of_numbers)
        list_activities.add_activity(id, str(people_id[1]), date, time, desc, [])
        date = datetime(2021, 12, 12, 12, 00, 00)
        with self.assertRaises(ServiceError): list_activities.add_activity('98', str(people_id[2]), date, time, desc, [])
    def test_update(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "98"
        date = datetime(2024, 12, 12, 12, 00, 00)
        time = "10:00:00"
        desc = "cooking"
        people = Person_services(list_of_numbers)
        people_id = people.get_listt()
        list_activities = Activity_services(list_of_numbers)
        list_activities.add_activity('100', people_id[1], date, time, desc, [])
        list_activities.update_activity('100', '99', people_id[1],date, time, desc, [])
        self.assertEqual(len(list_activities.get_all_activities()), 21)
    def test_update_duplicate(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "98"
        date = datetime(2022, 12, 12, 12, 00, 00)
        time = "10:00:00"
        desc = "cooking"
        people = Person_services(list_of_numbers)
        people_id = people.get_listt()
        list_activities = Activity_services(list_of_numbers)
        with self.assertRaises(ServiceError):list_activities.update_activity('-100', id, str(people_id[1]), date, time, desc, [])

    def test_remove(self):
        list_of_numbers = generate_unique_numbers(20, 100, 999)
        id = "99"
        date = datetime(2022, 12, 12, 12, 00, 00)
        time = "10:00:00"
        desc = "cooking"
        people = Person_services(list_of_numbers)
        people_id = people.get_listt()
        list_activities = Activity_services(list_of_numbers)
        list_activities.add_activity(id, str(people_id[1]), date, time, desc, [])
        list_activities.remove_activity(id)
        self.assertEqual(len(list_activities.get_all_activities()), 20)

    

if __name__ == '__main__':
    unittest.main()
