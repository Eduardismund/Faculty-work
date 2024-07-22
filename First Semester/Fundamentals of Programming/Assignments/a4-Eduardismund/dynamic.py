"""dynamic: 2.Given the set of positive integers S and the natural number k, display one of the subsets of S which sum
to k. For example, if S = { 2, 3, 5, 7, 8 } and k = 14, subset { 2, 5, 7 } sums to 14."""

def dynamic_naive(S, k, current_set, i):
    """
    This function uses a backtracking algorithm to obtain every possibility of creating a subset which sums up to
    k. being a recursive algorithm, it uses exponential time complexity
    :param S: the set given to create the subset from
    :param k: the number to which the subset has to sum up to
    :param current_set: the subset in course of creation
    :param i: the starting point/index in each search for a new element
    :return:the list 'results' with all the possible solutions
    """
    results=[]
    if k==0 and len(current_set)>1:
        results.append(current_set[:])
    if k<0 or i>len(S):
        return []
    else:
        for j in range(i, len(S)):
            if S[j]<=k:
                new_current_set = current_set.copy()
                new_current_set.append(S[j])
                results+=dynamic_naive(S, k - S[j], new_current_set,  j+1)
    return results



def dynamic_optimized(S, k):
    """
    This function calculates whether there exists a subset of the input set S that sums up to a given target value k
     and returns the subset if found. Additionally, it provides an option to inspect the dynamic programming table
     if command is
     set to 0
    :param S: the set given to create the subset from
    :param k: the number to which the subset has to sum up to
    :return: the subset if found
    """
    n = len(S)

    subset_sum= [[False] * (k + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        subset_sum[i][0] = True

    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if S[i - 1] > j:
                subset_sum[i][j] = subset_sum[i - 1][j]
            else:
                subset_sum[i][j] = subset_sum[i - 1][j] or subset_sum[i - 1][j - S[i - 1]]

    command=int(input("Press 0 to inspect the table or 1 otherwise: "))
    if command==0:
        print("   ", end="")
        for j in range(k + 1):
            print("{:4}".format(j), end=" ")
        print("\n")

        for i in range(n + 1):
            print("{:2} ".format(i), end="")
            for j in range(k + 1):
                print("{:4}".format(subset_sum[i][j]), end=" ")
            print()

    subset = []
    i, j = n, k
    while i > 0 and j > 0:
        if subset_sum[i][j] and not subset_sum[i - 1][j]:
            subset.append(S[i - 1])
            j -= S[i - 1]
        i -= 1

    return subset


def main():
    S = []
    while True:
        element_of_set = input("Enter an element for set S (press Enter to finish): ")
        if not element_of_set:
            break
        try:
            element_of_set = int(element_of_set)
        except ValueError:
            print("Invalid input. Please enter a valid element.")
            continue

        S.append(element_of_set)

    print("\nThe set S has the elements:", S)
    k=int(input("\nInsert a number k:"))

    print("\nUsing (naive) dynamic programming to find one of the subsets of S which sum to to k:")
    result=dynamic_naive(S,k, [], 0)
    ok=0
    for subset in result:
        print(subset)
        ok=1
        break
    if ok==0:
        print("->There is no subset in S that sums up to k")

    print("\nUsing dynamic programming to find one of the subsets of S which sum to to k:")
    results_d = dynamic_optimized(S, k)
    if not results_d:
        print("\n->There is no subset in S that sums up to k")
    else:
        print("\n", results_d)


main()