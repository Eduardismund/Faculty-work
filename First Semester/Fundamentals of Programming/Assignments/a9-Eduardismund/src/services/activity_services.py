from datetime import datetime, time
from random import randint, choice
from src.domain.Activities import Activity
from src.repository.ActivityRepo import RepoError
from src.services.undo_services import FunctionCall, Operation, CascadedOperation


class ServiceError(Exception):
    pass


class Activity_services:
    def __init__(self, list_of_numberss, repo, undo_service):
        """

        """
        self.__repo = repo
        self.__undo_service = undo_service
        self.generate_random_numbers(list_of_numberss)
        self.list_of_numbers = list_of_numberss

    @staticmethod
    def generate_unique_numbers(num_numbers, start_range, end_range):
        """
        static method to generate a set of numbers
        """
        unique_numbers = set()

        while len(unique_numbers) < num_numbers:
            random_number = randint(start_range, end_range)
            unique_numbers.add(random_number)

        return list(unique_numbers)

    def generate_random_numbers(self, list_of_numberss):
        """
        The 20 activities generated at start-up, having id, list of persons, date, time and description randomly generated
        """
        list_description = ["painting", "playing music", "reading", "running", "doing yoga", "cooking",
                            "folding laundry", "skating", "working-out", "playing video games"]
        list_of_numbers = self.generate_unique_numbers(20, 1000, 9999)
        for i in range(20):
            listT = []
            number = randint(1, 10)
            list_of_persons = self.generate_unique_numbers(int(number), 1, 19)
            for j in range(number):
                listT.append(list_of_numberss[list_of_persons[j]])
            j = 0
            for j in range(20 - number - 8):
                listT.append("    ")
            formated_date = datetime(randint(2023, 2026), randint(1, 12), randint(1, 28), randint(0, 23),
                                     randint(0, 59), randint(0, 59))
            timee = time(randint(0, 23), randint(0, 59), randint(0, 59))
            self.add_activity_at_startup(str(list_of_numbers[i]), listT, formated_date, str(timee),
                                         choice(list_description))

    def add_activity_at_startup(self, id, persons_id, formated_date, time, description):
        new_activity = Activity(id, persons_id, formated_date, time, description)
        try:
            self.__repo.add(new_activity)
        except RepoError:
            pass

    def add_activity(self, id, persons_id, formated_date, time, description, options):
        """
            creates an activity with input data from the ui and creates a new activity that should be added to the repo if the validity
           protocols are checked, otherwise a Service Error is raised
        """
        for i in range(len(persons_id)):
            ok = 0
            for j in range(len(options)):
                if persons_id[i] == options[j]:
                    ok = 1
            if ok == 0 and options != []:
                raise ServiceError("cannot add non-existent person ID's")
        new_activity = Activity(id, persons_id, formated_date, time, description)
        try:
            self.__repo.add(new_activity)
            redo_fun = FunctionCall(self.__repo.add, new_activity)
            undo_fun = FunctionCall(self.__repo.remove, id)
            self.__undo_service.record_undo(Operation(undo_fun, redo_fun))
        except RepoError:
            raise ServiceError("Cannot Add")

    def remove_activity(self, id):
        """
            removes an activity using the id, input data from the ui if the validity protocol is validated successfully
       """
        try:
            activity=self.__repo.get_activity(id)
            self.__repo.remove(id)
            redo_fun = FunctionCall(self.__repo.remove, id)
            undo_fun = FunctionCall(self.__repo.add, activity)
            self.__undo_service.record_undo(Operation(undo_fun, redo_fun))
        except RepoError:
            raise ServiceError("Cannot remove")

    def update_activity(self, old_id, new_id, new_list, new_formated_date, new_time, new_description, options):
        """
            updates an activity having a certain index, with new input data from the ui if the validity protocol is validated successfully
       """
        for i in range(len(new_list)):
            ok = 0
            for j in range(len(options)):
                if new_list[i] == options[j]:
                    ok = 1
            if ok == 0 and options != []:
                print("cannot update non-existent person ID's")
                raise ServiceError("cannot add non-existent person ID's")
        new_activity = Activity(new_id, new_list, new_formated_date, new_time, new_description)
        activity = self.__repo.get_activity(old_id)
        try:
            self.__repo.update(old_id, new_activity)
            redo_fun = FunctionCall(self.__repo.update, old_id, new_activity)
            undo_fun = FunctionCall(self.__repo.update, new_id, activity)
            self.__undo_service.record_undo(Operation(undo_fun, redo_fun))
        except RepoError:
            raise ServiceError("Cannot update")

    def search_activity_based_on_date(self, date):
        """
            searches a date in the dictionary(sending it to repo) and returns any occurrence that is partial or a complete match
        """
        return self.__repo.search_after_date(date)

    def search_activity_based_on_description(self, description):
        """
             searches a description in the dictionary(sending it to repo) and returns any occurrence that is partial or a complete match
        """
        return self.__repo.search_after_description(description)

    def get_activities_on_date(self, date):
        """
               searches a specific date in the dictionary and returns any occurrence that is a complete match
        """
        return self.__repo.get_activities_on_a_date(date)

    def get_activities_of_person(self, id):
        """
             searches a specific person using the id in the dictionary and returns any occurrence that is a complete match
        """
        return self.__repo.get_activities_of_p(id)

    def remove_all_occurences(self, id):
        """
         After a person is removed, its Id also flees from all the activities it belonged to, this function removing any
           occurrence there might exist
        """
        list_to_remove, list_of_activities = self.__repo.remove_all(id)
        accumulated_operations=[]
        for i in range(len(list_to_remove)):
            try:
                activity = self.__repo.get_activity(list_to_remove[i])
                self.__repo.remove(list_to_remove[i])
                redo_fun = FunctionCall(self.__repo.remove, list_to_remove[i])
                undo_fun = FunctionCall(self.__repo.add, activity)
                accumulated_operations.extend([Operation(undo_fun, redo_fun)])
            except RepoError:
                pass
        cascaded_operation = CascadedOperation(*accumulated_operations)
        self.__undo_service.record_undo(cascaded_operation)

    def get_statistic_date(self):
        """
        goes through all the dates from the dictionary and creates another dictionary having as index the date and as value
           the effective time
        """
        return self.__repo.get_stat_date()

    def get_all_activities(self):
        """
        lists all activities from the dictionary
        """
        return self.__repo.get_all()
