from ui.UI import UI
from repository.MemoryRepository import MemoryRepository
from repository.TextFileRepository import TextFileRepository
from repository.BinaryFileRepository import BinaryFileRepository
from repository.JSONRepository import JSONRepository
from src.tests.tests import Test

from jproperties import Properties

def test_all_reporsitories():
  memo_repo_test = MemoryRepository()
  text_repo_test = TextFileRepository("expenses_test.txt")
  bin_repo_test = BinaryFileRepository("expenses_test.bin")
  json_repo_test = JSONRepository("expenses_test.json")

    #memory
  tests_memory_repository = Test(memo_repo_test)
  tests_memory_repository.test_all()

    #textfile
  tests_text_repository = Test(text_repo_test)
  tests_text_repository.test_all()

    #bin
  tests_bin_repository = Test(bin_repo_test)
  tests_bin_repository.test_all()

    #Json
  tests_Json_repository = Test(json_repo_test)
  tests_Json_repository.test_all()

def use_properties():
    """a settings.properties file handles the type of repository that handles the memory location"""
    configs = Properties()
    with open('settings.properties', 'rb') as config_file:
        configs.load(config_file)

    repo_command = configs.get("REPO").data
    repo = "to_complete"
    print("The repository in use is: ", repo_command)
    if repo_command == "Memory":
        repo = MemoryRepository()

    elif repo_command == "Text":
        repo = TextFileRepository()

    elif repo_command == "Binary":
        repo = BinaryFileRepository()

    elif repo_command == "Json":
        repo = JSONRepository()

    return repo

test_all_reporsitories()
ui=UI(use_properties())
ui.print_ui()