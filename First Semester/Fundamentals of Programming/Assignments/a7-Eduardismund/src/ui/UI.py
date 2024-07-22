from src.services.ExpenseService import ExpenseServices

class UIError(Exception):
    pass
class UI:
    def __init__(self, repo):
        self.__expence_service= ExpenseServices(repo)

    def print_ui(self):
        while True:
            try:
                print("1. Add an expense")
                print("2. Display the list of expenses.")
                print("3. Filter the list so that it contains only expenses above a certain value read from the console.")
                print("4. Undo the last operation")
                print("5. Exit the application")

                option=input("Select an option: ")

                if option=='1':
                    day= input("Insert a day (integer number from 1-30): ")
                    amount= input("Insert an amount of money (positive integer number): ")
                    if not day.isnumeric() or not amount.isnumeric():
                        raise UIError("Please insert correct values\n")
                    if int(day)<1 or int(day)>30:
                        raise UIError("Please insert correct values\n")
                    type= input("Insert a type of expense: ")
                    self.__expence_service.add_expense(day, amount, type, True)

                elif option=="2":
                    expenses=self.__expence_service.get_all_expenses()
                    for expense in expenses:
                        print(expense)

                elif option=="3":
                    above_value=int(input("Insert an amount to filter numbers above it, deleting the ones below it: \n"))
                    self.__expence_service.filter_expense(above_value)

                elif option=="4":
                    self.__expence_service.undo_expense()

                elif option=="5":
                    print("bye")
                    break
                else:
                    print("not a valid option!\n")

                print()
            except UIError as ve:
                print(ve)

