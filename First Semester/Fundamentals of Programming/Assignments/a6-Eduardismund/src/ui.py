#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import copy

from functions import add, insert, remove_one, remove_two, replace, list_option, filter_option, undo, get_index, get_complex_number, generate_random
def show_menu():
    print("\tWelcome to my application!")
    print("\t--------------------------")
    print("\nToday a math teacher needs a program to help students test different properties"
          " of complex numbers, provided in the a+bi form\n")
    print("Choose one of the available commands from the categories below:")
    print("Category A: ADD A NUMBER\n")
    print("\tadd <number>\n\tinsert <number> at <position>\n")

    print("Category B: MODIFY NUMBER\n")
    print("\tremove <position>\n\tremove <start position> to <end position>\n\treplace <old number> with <new number>\n")

    print("Category C: DISPLAY NUMBERS HAVING DIFFERENT FUNCTIONALITIES\n")
    print("\tlist\n\tlist real <start position> to <end position>\n\tlist modulo [ < | = | > ] <number>\n")

    print("Category D: FILTER THE LIST\n")
    print("\tfilter real\n\tfilter modulo < 10\n\tfilter modulo > 6\t")

    print("Category E: UNDO\n")
    print("\tundo\t")

def added():
    print("-> The complex number has been added successfully!")

def removed():
    print("-> The complex number/s has/have been modified successfully!")

def filterr():
    print("-> The list of complex numbers has been filtered successfully!")

def display(list_complex_number, i):
    if get_index(list_complex_number[i]) != -1:
        print(str(get_index(list_complex_number[i])) + '. ' + get_complex_number(list_complex_number[i]))



def start_menu():

    show_menu()
    result=generate_random()
    safe=result
    copys=result
    operation_undo=[]
    operation_undo.append(copy.deepcopy(safe))

    while True:
        option=input("INSERT YOUR OPTION HERE: ").split()
        if option == []:
            print("->Not a valid command")
            print()
        else:
            try:
                if option[0] == "add":
                    add(result, option, operation_undo)
                    added()
                elif option[0] == "insert":
                    insert(result, option, operation_undo)
                    added()
                elif option[0] == "remove":
                    if "to" not in option:
                        remove_one(result, option, operation_undo)
                    else:
                        remove_two(result, option, operation_undo)
                    removed()
                elif option[0] == "replace":
                    replace(result, option, operation_undo)
                    removed()

                elif option[0] == "list":
                    to_display, i =list_option(result, option)
                    if i==1:
                        print("The list is in the current state, having the index, then the value displayed:")
                    elif i==2:
                        print("The real numbers between " + option[2] + " and " + option[4] + " are:")
                    elif i==3:
                        print("The numbers with modulo equal to " + option[3] + " are:")
                    elif i==4:
                        print("The numbers with modulo less than " + option[3] + " are:")
                    elif i==5:
                        print("The numbers with modulo greater than " + option[3] + " are:")

                    for i in range(len(to_display)):
                        display(to_display, i)
                    #
                elif option[0] == "filter":
                    filter_option(result, option, operation_undo)
                    filterr()
                elif option[0] == "undo":
                    result=undo(operation_undo, result)
                    if len(operation_undo)>1:
                        pass
                    else:
                        try:
                            result= operation_undo[0]
                        except IndexError:
                            print("Nothing to undo!")
                elif option[0]=="exit":
                    print("bye bye!")
                    break
                else:
                    print("Not a valid option...Try again!")

                print()
            except ValueError as ve:
                print(ve)
                print()