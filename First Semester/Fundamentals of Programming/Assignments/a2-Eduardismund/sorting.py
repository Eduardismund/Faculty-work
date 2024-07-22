from itertools import permutations
import random

def create_list(n, list):
    """
    This function creates the list of random numbers containing values from 0 to 100
    :param n: the length of the list
    :param list: the list in which all n elements will be saved
    """
    for i in range(0, n):
        a = random.randint(0, 100)
        list.append(a)
    print("The generated list is: ", list)
    input("Press Enter to continue...\n")

def sorted(arr):
    """
    This function is called to check if a certain permutation happens to be sorted, playing a big part in the Permutation Sort
    :param arr: the permutation sent as a list
    :return: True if the list is sorted and False otherwise
    """
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True

def permutation_sort(arr, nr):
    """
    The main function that helps to implement the Permutation Sort, calling other functions (e.g. permutations, sorted)
    and printing the process at certain steps
    :param arr: the list sent to be sorted
    :param nr: the steps that need to be printed
    :return: the sorted vector using the Permutation Sort
    """
    n = len(arr)
    i=1
    perms = permutations(arr)
    for perm in perms:
        if sorted(perm):
            return list(perm)
        else:
            if i%nr==0:
                print(perm)
            i=i+1
    return arr

def heapify(arr, n, i):
    """
    This function checks the left and right child nodes to determine the largest element and
    swaps it with the root node if necessary
    :param arr:  This is the input array that will be converted into a max heap
    :param n: the size of the heap
    :param i: index showing where a subtree is rooted
    """
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[i] < arr[left]:
        largest = left

    if right < n and arr[largest] < arr[right]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)
def heap_sort(arr, nr):
    """
    This function is called to perform the heap sort algorithm by building a max heap from the elements in the array
    :param arr: This is the input array that has to be sorted using the heap sort algorithm, modified in place
    :param nr: the step that prints the process of sorting
    """
    n = len(arr)
    j=1
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]  # Swap the root (max element) with the last element\
        if j % nr == 0:
            print(arr)
        j = j + 1
        heapify(arr, i, 0)
def main():
    list_numbers = []
    while True:
        print("1. Generate a list of random natural numbers")
        print("2. Sort the list using Permutation Sort")
        print("3. Sort the list using Heap Sort")
        print("4. Best case scenario for the Sorts above")
        print("0. Exit\n")

        while True:
            option = input(">")
            if not option.isnumeric():
                print("Pick a value between 0,1,2,3")
            else:
                option = int(option)
                if option > 3:
                    print("Pick a value between 0,1,2,3")
                else:
                    break

        if option == 1:
            list_numbers = []
            n = int(input("n="))
            create_list(n, list_numbers)

        if option == 0:
            print("bye")
            break

        if option == 3:
            if list_numbers:
                step = int(input("The step is:"))
                heap_sort(list_numbers, step)
                print("Sorted list using Heap Sort is:", list_numbers, "\n")
                input("Press Enter to continue...\n")
            else:
                print("First select 1 to create a list of random numbers!")
                input("Press Enter to continue...\n")

        if option == 2:
            if list_numbers:
                step = int(input("The step is:"))
                Psorted_list_numbers = permutation_sort(list_numbers, step)
                print("Sorted list using Permutation Sort is:", Psorted_list_numbers, "\n")
                input("Press Enter to continue...\n")
            else:
                print("First select 1 to create a list of random numbers!")
                input("Press Enter to continue...\n")

main()