#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import copy
from math import sqrt
from random import randint, choice


def manipulate_real(complex_number):
    """
    Extracts the real part of a complex number
    :param complex_number: the complex number
    :return: its real part
    """
    real=0
    if "i" not in complex_number:
        real = int(complex_number)
    else:
        for i in range(1, len(complex_number)):
            if complex_number[i]=="+" or complex_number[i]=="-":
                real=int(complex_number[0:i])
    return real


def manipulate_imaginary(complex_number):
    """
    Extracts the imaginary part of a complex number
    :param complex_number: the complex number
    :return: its imaginary part
    """
    imaginary = 0
    n=len(complex_number)
    if complex_number=="i":
        return 1
    if complex_number=="-i":
        return -1
    if "+" not in complex_number and "-" not in complex_number[1:] and "i" in complex_number:
        imaginary = int(complex_number.split("i")[0])
    else:
        if "-i" in complex_number:
            imaginary=-1
        elif "+i" in complex_number:
            imaginary=1
        elif "+" in complex_number:
            imaginary=int(complex_number[0:n-1].split("+")[1].split("i")[0])
        elif "-" in complex_number:
            imaginary = -1*int(complex_number[1:n - 1].split("-")[1].split("i")[0])
    return imaginary


def module(complex_number):
    """
    computes the module of a complex number
    :param complex_number: the complex number
    :return: its module
    """
    a=manipulate_real(complex_number)
    b=manipulate_imaginary(complex_number)
    return int(sqrt(a**2+b**2))


def create_new_number_at_index(complex_number, index):
    """
    dictionary with index and complex_number to store data
    """
    return {'index':index, 'complex_number':complex_number}

def get_complex_number(list):
    """
    accessing the complex number
    """
    return list['complex_number']

def get_index(list):
    """
    accessing the index
    """
    return list['index']

def generate_random():
    symbol=["+", '-']
    j=["i", ""]
    list=[]
    for i in range(10):
        number=str(randint(-100,100))+choice(symbol)+str(randint(1,100))+"i"
        list.append(create_new_number_at_index(number, i))

    return list
def is_valid_number(number):
    """
    checks whether a number can be a complex number or not
    :param number: the number to be checked
    :return: True or ValueError otherwise
    """
    try:
        if number=="0":
            return True
        if "_" in number:
            raise ValueError
        if "+" not in number and "-" not in number[1:]:
            if "i"==number or "-i"==number:
                number="1"

            if "i" in number and "i"!=number and "-i"!=number:
                number = number[:len(number) - 1]

            if int(number):
                return True
        else:

            if "+" in number:
                number = number.split("+")

                if int(number[0]) and number[1]=='i':
                    return True

                if int(number[0]) and int(number[1][:len(number[1]) - 1]):
                    return True
                if int(number[0]) and number[1]=='i':
                    return True

            if "-" in number[1:]:
                if "-" == number[0]:
                    number = number[1:].split("-")
                else:
                    number = number[0:].split("-")
                if int(number[0]) and int(number[1][:len(number[1]) - 1]):
                    return True
                if int(number[0]) and number[1]=='i':
                    return True
    except ValueError:
        raise ValueError("->Not a complex number where there should be! Try again!\n")


def add(list_complex_numbers, option, operation_undo):
    """
    adding a number to the list, doing so we check to see if the input command is right and then we add it to a dictionary,
    saved in a list afterward
    :param list_complex_numbers: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    """
    if len(option)>2 or len(option)==1:
        raise ValueError("Not a valid option...Try again!")

    ok=0
    for i in range(0, len(list_complex_numbers)):
        if get_index(list_complex_numbers[i])==-1 and is_valid_number(option[1]):
            if i!=0:
                list_complex_numbers[i]=(create_new_number_at_index(option[1], int(get_index(list_complex_numbers[i-1]))+1))
            else:
                list_complex_numbers[i] = (create_new_number_at_index(option[1], 0))
            ok = 1
            break

    if is_valid_number(option[1]) and ok==0:
            list_complex_numbers.append(create_new_number_at_index(option[1], len(list_complex_numbers)))
    operation=[]
    for i in list_complex_numbers:
        operation.append(i)

    operation_undo.append(copy.deepcopy(list_complex_numbers))


def insert(list_complex_numbers, option, operation_undo):
    """
    Insert command is part from the same class as Addition. if the insert command is invalid or it overwrites another number in the list,
    then a ValueError is raised. Otherwise, all index spaces until the inserted number are filled with 0 and at the correct index
    the number is inserted
    :param list_complex_numbers: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    :return:
    """

    if len(option)!=4 or option[2]!="at" or not int(option[3]):
        raise ValueError("->Incorrect command to insert")

    if len(list_complex_numbers)<=int(option[3]) and is_valid_number(option[1]):
        for i in range(len(list_complex_numbers), int(option[3])):
            list_complex_numbers.append(create_new_number_at_index('-1',-1))
        list_complex_numbers.append(create_new_number_at_index(option[1], int(option[3])))
    else:
        raise ValueError("Cannot insert a number on a position set already")
    operation = []
    for i in list_complex_numbers:
        operation.append(i)

    operation_undo.append(copy.deepcopy(list_complex_numbers))

def remove_one(list_complex_number, option, operation_undo):
    """
    It removes the number at a given index by overwriting '-1' over it and the program acts like it is not there
    :param list_complex_number: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    """

    if len(option)<2 or len(option)>2 or not int(option[1]) and int(option[1])!=0:
        raise ValueError("not a valid remove command")

    for i in range(len(list_complex_number)):
        if get_index(list_complex_number[i])==int(option[1]):
            list_complex_number[i]=create_new_number_at_index('-1',-1)
            operation = []
            for i in list_complex_number:
                operation.append(i)

            operation_undo.append(copy.deepcopy(list_complex_number))
            return

    raise ValueError("Oops, there is nothing to remove. Please try another command!")


def remove_two(list_complex_number, option, operation_undo):
    """
    It removes the number at a given index range by overwriting '-1' between the 2 given indexes and the program acts like
    those numbers are not there
    :param list_complex_number: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    """

    if 4>len(option) or len(option)>4 or not int ( int(option[1]) + int(option[3]) ) or option[2]!="to":
        raise ValueError("not a valid remove command")

    if len(list_complex_number)<int(option[1]):
        raise ValueError("Oops! Nothing to remove here. Please try another command!")

    for i in range(len(list_complex_number)):
        if int(option[1]) <= get_index(list_complex_number[i]) <= int(option[3]):
            list_complex_number[i]=create_new_number_at_index('-1',-1)

    operation = []
    for i in list_complex_number:
        operation.append(i)

    operation_undo.append(copy.deepcopy(list_complex_number))

def replace(list_complex_number, option, operation_undo):
    """
    checking the validity of numbers then we go through the list of complex numbers and we check if the number we had to find is
    in there. if yes, we replace the number with the one given
    :param list_complex_number: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    """
    operation = []
    ok=0

    if len(option)==4 and is_valid_number(option[1]) and is_valid_number(option[3]) and option[2]=="with":

        for i in range(len(list_complex_number)):

            if get_complex_number(list_complex_number[i])==option[1]:
                operation.append(create_new_number_at_index(option[3], i))
                list_complex_number[i]=create_new_number_at_index(option[3], i)
                ok=1
            else:
                operation.append(list_complex_number[i])
        if ok==0:
            raise ValueError("There is no complex number such as "+option[1]+" to replace. Try another value or another command!")
        operation_undo.append(operation)


    else:
        raise ValueError("-> Not a valid command for replace!")

def list_option(list_complex_number, option):
    """
    this function displays the current state of the list of complex numbers or between certain indexes
    the numbers to display are saved in a list and at the end returned
    :param list_complex_number: the list of dictionaries
    :param option: the command given
    """
    a=0
    ok=0
    to_display=[]
    if len(option)==1:
        a=1
        if len(list_complex_number)!=0:
            for i in range(len(list_complex_number)):
                if get_index(list_complex_number[i])!=-1:
                    to_display.append(list_complex_number[i])
                    j=1
                    ok=1

    elif len(option)==5 and option[1]=="real" and is_valid_number(option[2]) and manipulate_imaginary(option[4])==0 and manipulate_imaginary(option[4])!= 'i' and option[3]=="to":
        a=1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if int(option[2]) <= manipulate_real(get_complex_number(list_complex_number[i])) <= int(option[4]):
                    to_display.append(list_complex_number[i])
                    j=2
                    ok=1

    elif len(option)==4 and option[1]=="modulo" and option[2]=="=" and is_valid_number(option[3]):
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) == int(option[3]):
                    to_display.append(list_complex_number[i])
                    j=3
                    ok = 1

    elif len(option)==4 and option[1]=="modulo" and option[2]=="<" and is_valid_number(option[3]):
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) < int(option[3]):
                    to_display.append(list_complex_number[i])
                    j=4
                    ok = 1

    elif len(option)==4 and option[1]=="modulo" and option[2]==">" and is_valid_number(option[3]):
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) > int(option[3]):
                    to_display.append(list_complex_number[i])
                    j=5
                    ok = 1
    if a==1 and ok==0:
        raise ValueError("->Almost tricked me! There is nothing to display! (☞͡ ͜ʖ͡ )☞")
    if a==0 and ok==0:
        raise ValueError("->Common...that is not a valid command...ಠ_ಠ")
    return to_display, j

def filter_option(list_complex_number, option, operation_undo):

    """
    if it is a valid option, we make sure the conditions are satisfied and each number that does not fulfill the filter
    option is marked with -1 and not shown further
    :param list_complex_number: the list of dictionaries
    :param option: the command given
    :param operation_undo: helping the undo command
    """
    a = 0
    ok = 0
    if len(option) == 2 and option[1]=="real" and list_complex_number!=[]:
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if manipulate_imaginary(get_complex_number(list_complex_number[i])) != 0:
                    list_complex_number[i]=create_new_number_at_index('-1',-1)
                    ok=1

    elif len(option)==4 and option[1]=="modulo" and option[2]==">" and is_valid_number(option[3]) and list_complex_number!=[]:
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) <= int(option[3]):
                    list_complex_number[i]=create_new_number_at_index('-1', -1)
                    ok = 1

    elif len(option)==4 and option[1]=="modulo" and option[2]=="=" and is_valid_number(option[3]) and list_complex_number!=[]:
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) != int(option[3]):
                    list_complex_number[i]=create_new_number_at_index('-1', -1)
                    ok = 1

    elif len(option)==4 and option[1]=="modulo" and option[2]=="<" and is_valid_number(option[3]) and list_complex_number!=[]:
        a = 1
        if len(list_complex_number) != 0:
            for i in range(len(list_complex_number)):
                if module(get_complex_number(list_complex_number[i])) >= int(option[3]):
                    list_complex_number[i]=create_new_number_at_index('-1', -1)
                    ok = 1

    if a==0 and ok==0:
        raise ValueError("->Common...that is not a valid command...ಠ_ಠ")

    operation = []
    for i in list_complex_number:
        operation.append(i)

    operation_undo.append(copy.deepcopy(list_complex_number))

def undo(operations, result):
    """
    each operation is saved in a list of operations, and each time undo is called, the last thing saved on it is popped
    and the current list gets the last operation done
    :param operations: the list of operations
    """
    if len(operations)==0:
        raise ValueError("->Hello!? Nothing to undo anymore! (¬_¬)")
    else:
        result = operations[-1]
        operations.pop()
        print("Yummy, the last operation was undone successfully! (˘‿˘)✨")
    return result


def test_functions():
    #ADD
    list=[]
    try:
        add(list, "add 4+2".split(), [])
        assert False
    except ValueError:
        assert True

    try:
        add(list, "add 4+2i".split(), [])
        assert True
    except ValueError:
        assert False

    try:
        add(list, "add 7".split(), [])
        assert True
    except ValueError:
        assert False

    #INSERT
    try:
        insert(list, "insert i at 0".split(), [])
        assert False
    except ValueError:
        assert True

    try:
        insert(list, "insert -2i at 2".split(), [])
        assert True
    except ValueError:
        assert False

    #MODIFY

    try:
        remove_one(list, "remove 0".split(), [])
        assert True
    except ValueError:
        assert False

    try:
        remove_two(list, "remove 0 to 0".split(), [])
        assert False
    except ValueError:
        assert True

    try:
        replace(list, "replace -2i with 2i".split(), [])
        assert True
    except ValueError:
        assert False

    try:
        replace(list, "replace 100i with 1000".split(), [])
        assert False
    except ValueError:
        assert True

    #LIST

    try:
        list_option(list, "list < 10".split())
        assert False
    except ValueError:
        assert True

    try:
        list_option(list, "list".split())
        assert True
    except ValueError:
        assert False

    try:
        list_option(list, "list real".split())
        assert False
    except ValueError:
        assert True

    #Filter

    try:
        filter_option(list, "filter real 7".split(), [])
        assert False
    except ValueError:
        assert True

    try:
        filter_option(list, "filter".split(), [])
        assert False
    except ValueError:
        assert True

    #UNdo

    try:
        undo([{'index': -1, 'complex_number': '-1'}, {'index': 1, 'complex_number': '7'}, {'index': 2, 'complex_number': '2i'}], [])
        assert True
    except ValueError:
        assert False

    try:
        undo([], [])
        assert False
    except ValueError:
        assert True