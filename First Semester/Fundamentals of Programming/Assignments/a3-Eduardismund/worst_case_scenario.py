from best_case_scenario import create_list
from heap_sort import heap_sort_2
from runtime_functions import runtime_permutation, runtime_heap

def wc():
    """
        the main function that serves in obtaining the worst case scenario for both Permutation Sort and Heap Sort
    """
    for i in range(1, 6):
        list_worst_case = []
        create_list(1 * (2 * i), list_worst_case)
        heap_sort_2(list_worst_case)
        list_worst_case.reverse()

        runtime_permutation(list_worst_case, i)

        create_list(1000 * (2 ** i), list_worst_case)
        list_worst_case.reverse()

        runtime_heap(list_worst_case, i)

        if i <= 4:
            input("Press Enter to continue to the next list runtime...\n")
        else:
            print("Conclusion:\n  The worst-case scenario for permutation sort is when the algorithm must generate all possible permutations of the input array before finding the sorted permutation. This is why it is sorted, then reversed: to make sure the best case is no longer an option. The worst-case time complexity is O((n+1)!), where n is the number of elements in the input array. This is a factorial time complexity, which grows extremely quickly and makes the algorithm completely impractical for any reasonably sized input.")
            print(" In the worst-case scenario, where the input array is in reverse order, heap sort still exhibits a time complexity of O(n log n). This is because heap sort first builds a max-heap from the input array, which takes O(n) time, and then repeatedly removes the maximum element from the heap and restores the heap property, which takes O(log n) time for each removal. Since the removal operation is performed n times, the total time complexity remains O(n log n) in the worst case.")
            input("Press Enter to return to the menu...\n")