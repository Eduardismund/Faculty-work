from average_case_scenario import ac
from best_case_scenario import bc, create_list
from permutation_sort import permutation_sort_1
from heap_sort import heap_sort_1
from worst_case_scenario import wc

def main():
    list_numbers = []
    while True:
        print("1. Generate a list of random natural numbers")
        print("2. Sort the list using Permutation Sort")
        print("3. Sort the list using Heap Sort")
        print("4. Best case scenario for the Sorts above")
        print("5. Average case scenario for the Sorts above")
        print("6. Worst case scenario for the Sorts above")
        print("0. Exit\n")

        while True:
            option = input(">")
            if not option.isnumeric():
                print("Pick a value between 0,1,2,3,4,5,6")
            else:
                option = int(option)
                if option >= 7:
                    print("Pick a value between 0,1,2,3,4,5,6")
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
                heap_sort_1(list_numbers, step)
                print("Sorted list using Heap Sort is:", list_numbers, "\n")
                input("Press Enter to continue...\n")
            else:
                print("First select 1 to create a list of random numbers!")
                input("Press Enter to continue...\n")

        if option == 2:
            if list_numbers:
                step = int(input("The step is:"))
                Permutation_sorted_list_numbers = permutation_sort_1(list_numbers, step)
                print("Sorted list using Permutation Sort is:", Permutation_sorted_list_numbers, "\n")
                input("Press Enter to continue...\n")
            else:
                print("First select 1 to create a list of random numbers!")
                input("Press Enter to continue...\n")

        if option == 6:
            wc()
        if option == 5:
            ac()
        if option == 4:
            bc()
main()