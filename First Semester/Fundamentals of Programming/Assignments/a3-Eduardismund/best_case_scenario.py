import random
import time

from heap_sort import heap_sort_2
from permutation_sort import permutation_sort_2
from runtime_functions import runtime_permutation, runtime_heap

def create_list(n, list):
    """
    This function creates the list of random numbers containing values from 0 to 100
    :param n: the length of the list
    :param list: the list in which all n elements will be saved
    """
    for i in range(0, n):
        a = random.randint(0, 100)
        list.append(a)
    #print("The generated list is: ", list)
    # input("Press Enter to continue...\n")


def bc():
    """
    the main function that serves in obtaining the best case scenario for both Permutation Sort and Heap Sort
    """
    for i in range(0, 5):
        list_best_case = []
        create_list(1000 * (2 ** i), list_best_case)
        heap_sort_2(list_best_case)  # preparation

        print(f'# List number {str(i+1)}: {str(1000 * (2 ** i))} elements ordered in ascending order using Permutation Sort')
        start_time = time.time()
        sorted_list_p = permutation_sort_2(list_best_case)
        end_time = time.time()
        print(f'->Runtime for Heap Sort: {str((end_time - start_time) * 1000)} milliseconds\n')

        print(f'# List number {str(i+1)}: {str(1000 * (2 ** i))} elements ordered in ascending order using Heap Sort')
        start_time = time.time()
        heap_sort_2(list_best_case)
        end_time = time.time()
        print(f'->Runtime for Heap Sort: {str((end_time - start_time) * 1000)} milliseconds\n')


        if i <= 3:
            input("Press Enter to continue to the next list runtime...\n")
        else:
            print("Conclusion:\n The best-case time complexity for permutation sort is difficult to define "
                  "precisely because it relies on random chance. The best-case scenario for permutation sort "
                  "is that the input list is already sorted. In this case, the algorithm would only require "
                  "one check to determine that the list is already sorted -O(1)- and no further permutations "
                  "would be necessary.")
            print(" The best-case scenario for the Heap Sort algorithm is when the input array is already "
                  "sorted in ascending order. In this situation, the elements are in their optimal positions "
                  "relative to the binary heap structure, making it more efficient than the average or "
                  "worst-case scenarios.In a sorted array, the heapification step can be accomplished in "
                  "linear time because there is little need to swap elements. The overall time complexity of "
                  "Heap Sort in the best-case scenario is O(n * log n), which is the same as the worst-case "
                  "and average-case scenarios. However, the constant factors involved in the best-case "
                  "scenario are smaller because of the initial sorted state")
            input("Press Enter to return to the menu...\n")