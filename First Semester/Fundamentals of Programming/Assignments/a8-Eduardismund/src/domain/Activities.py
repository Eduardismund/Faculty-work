from datetime import datetime


class Activity:
    def __init__(self, activity_id: str, person_id : list, date: datetime, time, description: str):
        self._id = activity_id
        self._list = person_id
        self._description = description
        self._date = date
        self._time = time

    @property
    def get_id(self):
        return self._id

    @property
    def get_list(self):
        return self._list

    @property
    def get_date(self):
        return self._date

    @property
    def get_time(self):
        return self._time

    @property
    def get_description(self):
        return self._description

    def __str__(self):
        people_id=''
        for i in self._list:
            people_id+= str(i)+ " "
        return "Activity ID: "+ self._id + " | \t"+ "List of people ID: " + people_id + "| \t"+ "Date: " + str(self._date) + " | \tTime: " + str(self._time) + " | \tDescription: " + self._description