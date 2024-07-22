from datetime import datetime

from src.domain.Activities import Activity
from src.repository.ActivityRepo import ActivityRepo


class ActivityRepoTextFile(ActivityRepo):
    """
    data saved in 'activity.txt' and inherits all the methods and functions from MemoryRepository
    """

    def __init__(self, file_name="activity.txt"):
        """
            inherits the necessary methods and in addition it requires a file to which we load from
        """
        super(ActivityRepoTextFile, self).__init__()
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
            date=line[2].strip()
            time=line[3].strip()
            date1=date.split("-")
            time1=time.split(":")

            the_date= datetime(int(date1[0]), int(date1[1]), int(date1[2]), int(time1[0]), int(time1[1]), int(time1[2]))
            new_activity = Activity(line[0].strip(), line[1].split(), the_date, line[4].strip(), line[5].strip())
            super().add(new_activity)

    def save_at_file(self):

        """
        writes the data back into the file
        """
        fout = open(self._file_name, "wt")
        for activity in self.get_all():
            the_date= str(activity._date).split()
            to_str=''
            for i in range(len(activity._list)):
                if activity._list[i]!='   ':
                    to_str+=str(activity._list[i])+" "
            activity_list = activity._id + ',' + to_str[:-1] + ',' + str(the_date[0]) + ',' + str(the_date[1])+ ','+ str(activity._time) + ','+str(activity._description) +"\n"
            fout.write(activity_list)

        fout.close()

    def add(self, new_activity):
        """
        inherited and the same as in memoryRepository
        """
        super().add(new_activity)
        self.save_at_file()

    def remove(self, activity_id):
        """
        inherited and the same as in memoryRepository
        """
        super().remove(activity_id)
        self.save_at_file()

    def update(self, activity_id, new_activity):
        """
        inherited and the same as in memoryRepository
        """
        super().update(activity_id, new_activity)
        self.save_at_file()
