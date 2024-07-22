from itertools import permutations
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
def permutation_sort_1(arr, nr):

    """
    The main function that helps to implement the Permutation Sort, calling other functions (e.g. permutations, sorted)
    and printing the process at certain steps
    :param arr: the list sent to be sorted
    :param nr: the steps that need to be printed
    :return: the sorted vector using the Permutation Sort
    """
    n = len(arr)
    i = 1
    perms = permutations(arr)
    for perm in perms:
        if sorted(perm):
            return list(perm)
        else:
            if i % nr == 0:
                print(perm)
            i = i + 1
    return arr


def permutation_sort_2(arr):
    """
    The main function that helps to implement the Permutation Sort
    :param arr: the list sent to be sorted
    :return: the sorted vector using the Permutation Sort
    """
    if sorted(arr):
        return list(arr)
    n = len(arr)
    perms = permutations(arr)
    for perm in perms:
        if sorted(perm):
            return list(perm)
    return arr