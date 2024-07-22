from best_case_scenario import create_list
from runtime_functions import runtime_permutation, runtime_heap

def ac():
    """
        the main function that serves in obtaining the average case scenario for both Permutation Sort and Heap Sort
    """
    for i in range(1, 6):
        list_average_case = []
        create_list(1 * (2 * i), list_average_case)

        runtime_permutation(list_average_case, i)

        create_list(1000 * (2 ** i), list_average_case)

        runtime_heap(list_average_case, i)
        if i <= 4:
            input("Press Enter to continue to the next list runtime...\n")
        else:
            print("Conclusion:\n  Permutation Sort's average-case time complexity is extremely difficult to analyze precisely because it relies on random chance. The algorithm generates random permutations of the input list and checks whether the list is sorted before each permutation. It continues generating permutations until it finds one that results in a sorted list. The average-case time complexity depends on the probability of generating a sorted permutation. The average number of permutations required to sort a list of size n is factorial (n), which grows extremely quickly (n! = 1 * 2 * 3 * ... * n). This is why the number of elements is considerably lower than the one for Heap Sort")
            print(" The average-case time complexity of Heap Sort is O(n * log n), which is the same as its worst-case time complexity. Heap Sort is a comparison-based sorting algorithm, and its performance remains consistent across various input distributions, which is a characteristic of O(n * log n) sorting algorithms. This means that Heap Sort performs well on average, regardless of whether the input data is nearly sorted or completely random. The average-case time complexity is determined based on the average number of comparisons and swaps required to sort the input data. In the case of Heap Sort, the binary heap structure ensures that these operations occur in O(log n) time for each element, resulting in an overall time complexity of O(n * log n) in the average case.")
            input("Press Enter to return to the menu...\n")