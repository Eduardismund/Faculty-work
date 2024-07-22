from datetime import datetime
from src.services.activity_services import Activity_services
from src.services.person_services import Person_services
from src.services.activity_services import ServiceError
from src.services.undo_services import UndoService, UndoError


class UIError(Exception):
    pass


class UI:
    def __init__(self, list_of_numbers, repo1, repo2):
        self.__undo_service = UndoService()
        self.__person_services = Person_services(list_of_numbers, repo2, self.__undo_service)
        self.__activity_services = Activity_services(list_of_numbers, repo1, self.__undo_service)

    def print_menu(self):
        while True:
            try:
                try:
                    print("     OPTIONS:")
                    print("---------------------")
                    print(" 1. Manage people and activities")
                    print(" 2. Search for persons or activities")
                    print(" 3. Create statistics")
                    print(" 4. Exit\n")

                    option1 = input("Insert one of the options above: ")

                    if option1 == "1":
                        self.manage_people_and_activities()
                    elif option1 == "2":
                        self.search_persons_and_activities()
                    elif option1 == "3":
                        self.create_statistics()
                    elif option1 == "4":
                        print("bye")
                        break
                    else:
                        print("Invalid Command")
                except UIError as ve:
                    print(ve)
            except ServiceError as ve:
                print(ve)

    def create_statistics(self):
        print("1. List the activities for a given date, in the order of their start time")
        print(
            "2. List the upcoming dates with activities, sorted in ascending order of the free time in that day")
        print("3. List all upcoming activities to which a given person will participate")
        option2 = input("Insert one of the options above:")
        if option2 == "1":
            dic = {}
            date = input("Insert an existing date:")
            activities = self.__activity_services.get_activities_on_date(date)
            if activities == []:
                print("Not an existing date!")
            for activity in activities:
                dic[activity.get_date] = activity
            sorted_dict = dict(sorted(dic.items()))
            for i in sorted_dict.values():
                print(i)

        elif option2 == "2":
            dic = {}
            date_dict = self.__activity_services.get_statistic_date()
            sorted_dict = dict(sorted(date_dict.items(), key=lambda item: item[1]))
            for i in sorted_dict:
                print(i)

        elif option2 == "3":
            dic = {}
            id = input("Insert a person ID: ")
            print("The person at id:" + id + " is:")
            print(self.__person_services.get_personn(id), "participating in the following activities: ")
            activities = self.__activity_services.get_activities_of_person(id)
            for activity in activities:
                print(activity)
        else:
            print("Invalid command!")

    def search_persons_and_activities(self):
        print("1. Search for a person using phone number.")
        print("2. Search for a person using name.")
        print("3. Search for an activity using the date.")
        print("4. Search for an activity using the description")
        option2 = input("Insert one of the options above: ")
        if option2 == "1":
            phone_number = input("Insert the phone number: ")
            telephones = self.__person_services.search_person_based_on_phone_number(phone_number)
            for telephone in telephones:
                print(telephone)
        elif option2 == "2":
            name = input("Insert the name: ")
            persons = self.__person_services.search_person_based_on_name(name)
            for person in persons:
                print(person)
        elif option2 == "3":
            date = input("Insert the date (YYYY-MM-DD): ")
            dates = self.__activity_services.search_activity_based_on_date(date)
            for date in dates:
                print(date)
        elif option2 == "4":
            desc = input("Insert the description: ")
            descriptions = self.__activity_services.search_activity_based_on_description(desc)
            for description in descriptions:
                print(description)
        else:
            print("Not a valid command!")

    def manage_people_and_activities(self):
        print("     Options for Persons:")
        print("1. Add a person")
        print("2. Remove a person")
        print("3. Update a person")
        print("4. List all persons\n")
        print("     Options for Activities:")
        print("5. Add an activity")
        print("6. Remove an activity")
        print("7. Update an activity")
        print("8. List all activities\n")
        print("     Other Options:")
        print("9. Undo the last operation that modified the lists")
        print("10. Redo the last operation that modified the lists")
        option2 = input("Insert one of the options above: \n")
        # PERSON
        if option2 == "1":
            id = input("Insert an ID: ")
            phone_number = input("Insert a phone number: ")
            name = input("Insert a name: ")
            if not id.isnumeric():
                raise UIError("The ID is not numeric!")
            self.__person_services.add_person(id, phone_number, name)

        elif option2 == "2":
            id = input("Insert the ID of the person to be removed: ")
            if not id.isnumeric():
                raise UIError("The ID is not valid!")
            self.__person_services.remove_person(id)
            self.__activity_services.remove_all_occurences(id)

        elif option2 == "3":
            old_id = input("Insert the old ID: ")
            new_id = input("Insert the new ID: ")
            phone_number = input("Insert the new phone number: ")
            name = input("Insert the new name: ")
            if not old_id.isnumeric() or not new_id.isnumeric():
                raise UIError("The ID is not numeric!")
            self.__person_services.update_person(old_id, new_id, phone_number, name)

        elif option2 == "4":
            persons = self.__person_services.get_all_persons()
            for person in persons:
                print(person)

        # ACTIVITY

        elif option2 == "5":
            id = input("Insert an activity ID: ")
            persons_id = input(
                "Insert a list of (existing) persons ID's participating in the activity: ").split()
            date = input("Insert the date of the activity (YYYY-MM-DD) : ")
            date_time = input("On that date, the starting time is (HH:MM:SS): ")
            time = input("Insert the effective time of the activity: ")
            description = input("Insert a description for this activity: ")
            options = self.__person_services.get_listt()
            if not id.isnumeric():
                raise UIError("The ID is not numeric!")
            formatted_date = 0
            formatted_date = self.check_valability_date(date, date_time, formatted_date)
            try:
                self.__activity_services.add_activity(id, persons_id, formatted_date, time, description,
                                                      options)
            except ServiceError:
                print("Invalidity")

        elif option2 == "6":

            id = input("Insert an activity ID to remove: ")
            if not id.isnumeric():
                raise UIError("The ID is not valid!")
            self.__activity_services.remove_activity(id)

        elif option2 == "7":
            old_id = input("Insert the old activity ID: ")
            new_id = input("Insert the new activity ID: ")
            new_list = input(
                "Insert a new list of (existing) persons ID's participating in the activity: ").split()
            new_date = input("Insert the date of the new activity (YY-MM-DD) : ")
            new_date_time = input("On that date, the starting time is (HH:MM:SS): ")
            new_time = input("Insert the effective time of the new activity: ")
            new_description = input("Insert a description for the new activity: ")
            new_formatted_date = 0
            options = self.__person_services.get_listt()
            new_formatted_date = self.check_valability_date(new_date, new_date_time, new_formatted_date)
            if not old_id.isnumeric() or not new_id.isnumeric():
                raise UIError("The ID is not numeric!")
            try:
                self.__activity_services.update_activity(old_id, new_id, new_list, new_formatted_date,
                                                         new_time, new_description, options)
            except ValueError:
                print("Invalidity!")

        elif option2 == "8":
            activities = self.__activity_services.get_all_activities()
            for activity in activities:
                print(activity)
        elif option2 == "9":
            try:
                self.__undo_service.undo()
            except UndoError:
                print("No more undo's")
        elif option2 == "10":
            try:
                self.__undo_service.redo()
            except UndoError:
                print("No more redo's")

    def check_valability_date(self, new_date, new_date_time, new_formatted_date):
        try:
            try:
                date_array = new_date.split("-")
                date_time_array = new_date_time.split(":")
                new_formatted_date = datetime(int(date_array[0]), int(date_array[1]),
                                              int(date_array[2]),
                                              int(date_time_array[0]), int(date_time_array[1]),
                                              int(date_time_array[2]))
            except ValueError:
                print("invalid input")
        except IndexError:
            print("Not the correct format for date/time")
        return new_formatted_date
