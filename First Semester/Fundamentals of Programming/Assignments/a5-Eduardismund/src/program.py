#
# Write the implementation for A5 in this file
#
import random
from math import sqrt



#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
"""
def get_real(list):
    return list[0]

def get_imaginary(list):
    return list[1]
def create_complex(a, b):
    return [a,b]
"""
#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def get_real(dic):
    return dic['real']

def get_imaginary(dic):
    return dic['imaginary']
def create_complex(a, b):
    return {'real': a, 'imaginary':b}

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def mainupulate_real(complex_number):
    real=0
    if "i" not in complex_number:
        real = int(complex_number)
    else:
        for i in range(1, len(complex_number)):
            if complex_number[i]=="+" or complex_number[i]=="-":
                real=int(complex_number[0:i])
    return real

def manipulate_imaginary(complex_number):
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
def create_complex_list(list):
    complex_numbers=[]

    for i in range(0, len(list)):
        real=mainupulate_real(list[i])
        imaginary=manipulate_imaginary(list[i])
        complex_numbers.append(create_complex(real, imaginary))
    return complex_numbers


def generate_random_complex_numbers():
    l = []
    for i in range(10):
        l.append(create_complex(random.randint(-100, 100), random.randint(-100, 100)))
    return l

def compare(array, digit_count):
    if str(array)!="0":
        for digit in str(array):
            if digit in digit_count:
                digit_count[digit] = 1

def check(dic1, dic2):
    for digit in "0123456789":
        if dic1[digit]+dic2[digit]==1:
            return False
    return True
def same_digit(array1, array2):
    contor1 = {str(i): 0 for i in range(10)}
    contor2 = {str(i): 0 for i in range(10)}
    compare(get_real(array1), contor1)
    compare(get_imaginary(array1), contor1)
    compare(get_real(array2), contor2)
    compare(get_imaginary(array2), contor2)
    return check(contor1,contor2)

def longest_subarray_base_10(array):
    """
    Function for solving 3A. If the digits forming 2 consecutive numbers are the same, a subarray starts forming
    increasing in length. when this condition is no longer met, the subarray is checked if it is the maximum one until
    that point, and if it so, the subarray is saved. this checking is performed once again after exiting the loop.
    :param array: the list of lists/dictionaries representing complex numbers
    :return: the subarray and the maximum length with the required condition
    """
    subarray = [array[0]]
    length = 1
    max_length = 0
    subarray_max = []

    for i in range(1, len(array)):
        if same_digit(array[i - 1], array[i]):
            length += 1
            subarray.append(array[i])
        else:
            if length >= max_length:
                max_length = length
                subarray_max = subarray[:]
            length = 1
            subarray = [array[i]]

    if length >= max_length:
        max_length = length
        subarray_max = subarray[:]

    return subarray_max, max_length

def module(complex_number):
    a=get_real(complex_number)
    b=get_imaginary(complex_number)
    return int(sqrt(a**2+b**2))

def create_mod_sequence(list):
    sequence = [module(c) for c in list]
    return sequence
def longest_alternating_subsequence(seq):
    """
    Function for solving 3B. considering an alternating subsequence can be increasing or decreasing, and they both
     depend on eachother, the dynamic solving is done so. in a nested for, if an element is creating an increasing
     subsequence and the lists permit so, it will be added to either the increasing one or to the decreasing one. at the
     end, the maximum value from each array is taken into consideration and returned
    :param seq: the sequence needed to be searched through
    :return: the maximum length of a subsequence
    """
    n = len(seq)
    inc_len = [1] * n
    dec_len = [1] * n

    for i in range(1, n):
        for j in range(i):
            if seq[i] > seq[j] and inc_len[i] <= dec_len[j] + 1:
                inc_len[i] = dec_len[j] + 1
            elif seq[i] < seq[j] and dec_len[i] <= inc_len[j] + 1:
                dec_len[i] = inc_len[j] + 1

    max_len = max(max(inc_len), max(dec_len)) if n > 0 else 0

    return max_len

def read_numbers():
    lst=[]

    lst=[item for item in input("Enter the list of complex numbers by the standard form of 'a+bi': ").split(", ")]
    return lst

def available_commands():
    print("       MENU:")
    print("1. Read a list of complex numbers")
    print("2. Display the list of read complex numbers")
    print("3a. Display length and elements of a longest subarray of numbers where both their real and imaginary parts "
          "can be written using the same base 10 digits")
    print("3b. Display The length of a longest alternating subsequence, when considering each number's modulus")
    print("4. Exit")


def display_list(list):
    print("   ->The list of complex numbers is:")
    for number in list:
        if get_imaginary(number)>1:
            print(str(get_real(number))+"+"+str(get_imaginary(number))+"i", end="  ")
        elif get_imaginary(number)<-1:
            print(str(get_real(number)) + str(get_imaginary(number)) + "i", end="  ")
        elif get_imaginary(number)==1:
            print(str(get_real(number)) + "+i", end="  ")
        elif get_imaginary(number) == -1:
            print(str(get_real(number)) + "-i", end="  ")
        else:
            print(str(get_real(number)), end="  ")

def display_maximum_subarray(array, length):
    print("   ->The length and elements of a longest subarray of numbers where both their real and imaginary parts can be"
          " written using the same base 10 digits are: ", length)
    display_list(array)
def display_3b(n, seq):
    print("   ->The length of a longest alternating subsequence from the sequence", seq, "is: ", n)

def end_of_function():
    print("   ->Thank you for choosing my application! :-)")

def reenter_loop():
    input("\n   ->Press ENTER to return to the MENU and choose another command (or a valid one)!\n")

def menu():
    list__numbers=[]
    list_complex_numbers=generate_random_complex_numbers()
    while True:
        available_commands()
        option=input("Choose an option between 1/2/3a/3b/4: ")
        if option=="1":
            list__numbers+=read_numbers()
            list_complex_numbers+=create_complex_list(list__numbers)
        elif option=="2":
            display_list(list_complex_numbers)
        elif option=="3a":
            maximum_subarray, length=longest_subarray_base_10(list_complex_numbers)
            display_maximum_subarray(maximum_subarray, length)
        elif option=="3b":
            seq=create_mod_sequence(list_complex_numbers)
            display_3b(longest_alternating_subsequence(seq), seq)
        elif option=="4":
            end_of_function()
            break
        reenter_loop()



# Ideally, this section should not contain any calculations relevant to program functionalities
#

if __name__ == "__main__":
    menu()
