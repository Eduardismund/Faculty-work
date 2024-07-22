import time
from heap_sort import heap_sort_2
from permutation_sort import permutation_sort_2


def runtime_heap(arr, i):
    """
    This function computes the actual time it takes for Heap Sort to complete its task
    :param arr: the list that has to be sorted
    :param i:  the index corresponding to the list, with values between 1 and 5 included
    """
    print(f'# List number {str(i)}: {str(1000 * (2 ** i))} elements ordered in ascending order using Heap Sort')
    start_time = time.time()
    heap_sort_2(arr)
    end_time = time.time()
    print(f'->Runtime for Heap Sort: {str((end_time - start_time) * 1000)} milliseconds\n')

def runtime_permutation(arr, i):
    """
        This function computes the actual time it takes for Permutation Sort to complete its task
        :param arr: the list that has to be sorted
        :param i:  the index corresponding to the list, with values between 1 and 5 included
    """
    print(f'# List number {str(i)}: {str(1 * (2 * i))} elements ordered in ascending order using Permutation Sort')
    start_time = time.time()
    sorted_list_p = permutation_sort_2(arr)
    end_time = time.time()
    print(f'->Runtime for Permutation Sort: {str((end_time - start_time) * 1000)} milliseconds')