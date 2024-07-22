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


def heap_sort_1(arr, nr):
    """
    This function is called to perform the heap sort algorithm by building a max heap from the elements in the array
    :param arr: This is the input array that has to be sorted using the heap sort algorithm, modified in place
    :param nr: the step that prints the process of sorting
    """
    n = len(arr)
    j = 1
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]  # Swap the root (max element) with the last element\
        if j % nr == 0:
            print(arr)
        j = j + 1
        heapify(arr, i, 0)


def heap_sort_2(arr):
    """
    This function is called to perform the heap sort algorithm by building a max heap from the elements in the array
    :param arr: This is the input array that has to be sorted using the heap sort algorithm, modified in place
    """
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)