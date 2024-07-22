from datetime import timedelta, time, datetime


class RepoError(Exception):
    """
        The exception raised in the class below
    """
    pass
class ActivityRepo:
    '''
    class that manages activities
    '''
    def __init__(self):
        self._data = {}

    def add(self, new_activity):
        """
            adding an activity if its id is not already in use, else raising an error. Also validates if activities do not
            overlap one another with 'check'
        """
        check=1
        if self._data!={}:
            check= self.checkif(new_activity)
        if new_activity._id not in self._data and check==1:
            self._data[new_activity._id] = new_activity
        else:
            raise RepoError("Cannot add an activity ID already in use or people already in other activities")

    def remove(self, activity_id):
        """removes an activity if found in the list otherwise raises an Error either by not having the id to delete or
                by reaching the end of the dictionary"""
        if self._data=={}:
            raise RepoError("Nothing to remove here!\n")
        if activity_id in self._data:
            del self._data[activity_id]
        else:
            raise RepoError("Cannot remove an ID not in use.\n")

    def checkif(self, new_activity):
        """
        function to validate the dates already in the memory. it iterates over the dictionary of activities and decides whether
        the activity to be added would create an overlap or not, returning 1 in the first case and 0 in the latter
        """
        ok = 0
        for i in range(len(new_activity._list)):
            start = new_activity._date
            co = new_activity._time.split(":")
            duration=timedelta(hours=int(co[0]), minutes=int(co[1]), seconds=int(co[2]))
            end = new_activity._date + duration
            for activity in self._data.values():
                start1 = activity._date
                co = activity._time.split(":")
                end1 = activity._date + timedelta(hours=int(co[0]), minutes=int(co[1]), seconds=int(co[2]))
                if (start < end < start1 < end1) or (start1 < end1 < start < end) or (start == start1 and end==end1):
                    ok = 1
                else:
                    ok = 0
        return ok

    def update(self, activity_id, new_activity):
        """
            updates an old activity id with a new one, if there is nothing to update or the id doesnt exist, an error
            will be raised, also the validity is also checked with the 'checkif' function
       """
        check = 1
        if self._data != {}:
            check = self.checkif(new_activity)
        if activity_id in self._data and check==1:
            self._data[activity_id] = new_activity
            new_dict = {new_activity._id if old_key == activity_id else old_key: value for old_key, value in
                        self._data.items()}
            self._data = new_dict
        else:
            raise RepoError("Cannot update an ID not in use.\n")

    def search_after_date(self, date):
        """
            searches a date in the dictionary and returns any occurrence that is partial or a complete match
        """
        occurrences=[]
        for obj in self._data.values():
            obj_date=str(obj._date)
            if str(date) in obj_date:
                occurrences.append(obj)
        return occurrences

    def search_after_description(self, description):
        """
            searches a description in the dictionary and returns any occurrence that is partial or a complete match
        """
        occurrences=[]
        desc=description.lower()
        for obj in self._data.values():
            descc=obj._description.lower()
            if desc in descc:
                occurrences.append(obj)
        return occurrences

    def get_activity(self, id):
        if id in self._data:
            return self._data[id]
        else:
            return "Not an existing activity"

    def get_activities_on_a_date(self, date):
        """
        searches a specific date in the dictionary and returns any occurrence that is a complete match
        """
        occurrences = []
        for obj in self._data.values():
            datee=str(obj._date).split()
            if date == datee[0]:
                occurrences.append(obj)
        return occurrences


    def remove_all(self, id):
        """
        After a person is removed, its Id also flees from all the activities it belonged to, this function removing any
        occurrence there might exist
        """
        to_remove=[]
        all_activities=[]
        for activity in self._data.values():
            for i in range(len(activity._list)):
                if str(activity._list[i])==str(id):
                    to_remove.append(activity._id)
                    all_activities.append(activity)
        return to_remove, all_activities

    def get_activities_of_p(self, id):
        """
            searches a specific person using the id in the dictionary and returns any occurrence that is a complete match
        """
        occurrences = []
        for obj in self._data.values():
            #print(id, " ", obj._list)
            listt=obj._list
            for i in range(len(listt)):
                #print(id, listt[i])
                if str(id)==str(listt[i]):
                    #print(obj)
                    occurrences.append(obj)

        #print(occurrences)
        return occurrences
    def get_stat_date(self):
        """
        goes through all the dates from the dictionary and creates another dictionary having as index the date and as value
        the effective time
        """
        dic={}
        timeee=datetime(1,1,1, 0, 0, 0)
        for obj in self._data.values():
            dataa=str(obj._date).split()
            dic[dataa[0]]=timeee

        for obj in self._data.values():
            timee=obj._time.split(":")
            dataa=str(obj._date).split()
            dic[dataa[0]] += timedelta(days=0, hours=int(timee[0]), minutes=int(timee[1]), seconds=int(timee[2]))
        return dic

    def get_all(self):
        """
                :return: all the values from the dictionary, the activity data
                """
        return list(self._data.values())