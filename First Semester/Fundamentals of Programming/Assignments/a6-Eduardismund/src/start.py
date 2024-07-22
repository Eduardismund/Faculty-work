#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from functions import test_functions
from ui import start_menu

def start_up():

    start_menu()

    test_functions()

if __name__=="__main__":
    start_up()