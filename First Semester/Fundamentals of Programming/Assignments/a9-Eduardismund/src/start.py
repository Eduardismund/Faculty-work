from random import randint
from jproperties import Properties
from src.repository.ActivityRepo import ActivityRepo
from src.repository.ActivityRepoBinaryFile import ActivityRepoBinaryFile
from src.repository.ActivityRepoTextFile import ActivityRepoTextFile
from src.repository.PersonRepo import PersonRepo
from src.repository.PersonRepoBinaryFile import PersonRepoBinaryFile
from src.repository.PersonRepoTextFile import PersonRepoTextFile
from src.ui.UI import UI

def use_properties():
    """a settings.properties file handles the type of repository that handles the memory location"""
    configs = Properties()
    with open('settings.properties', 'rb') as config_file:
        configs.load(config_file)

    repo_command = configs.get("repository").data
    person = configs.get("person").data
    activity = configs.get("activity").data
    a=activity[1:-1]
    p= person[1:-1]
    repo1 = ''
    repo2 = ''
    print("The repository in use is: ", repo_command)
    if repo_command == "inmemory":
        repo1 = ActivityRepo()
        repo2 = PersonRepo()

    elif repo_command == "binaryfiles":
        repo1 = ActivityRepoBinaryFile(a)
        repo2 = PersonRepoBinaryFile(p)

    elif repo_command == "textfiles":
        repo1 = ActivityRepoTextFile(a)
        repo2 = PersonRepoTextFile(p)

    return repo1, repo2
def generate_unique_numbers(num_numbers, start_range, end_range):
    unique_numbers = set()

    while len(unique_numbers) < num_numbers:
        random_number = randint(start_range, end_range)
        unique_numbers.add(random_number)
    return list(unique_numbers)

repo1, repo2 = use_properties()
list_of_numbers = generate_unique_numbers(20, 1000, 9999)
ui = UI(list_of_numbers, repo1, repo2)
ui.print_menu()
