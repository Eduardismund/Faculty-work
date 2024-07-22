"""backtracking: 2.Consider a positive number n. Determine all its decompositions as sums of prime numbers."""

def its_prime(n: int):
    """
    function that checks if n is prime or not
    :param n: number to be studied
    :return: true or false
    """
    if n<=1:
        return False
    for i in range (2, int(n**0.5)+1):
        if n%i==0:
            return False
    return True

def iterative(n):
    """
    this function uses a stack to mimic a recursive call, but in an iterative manner. each time a new prime number between 2 and n is found, it is
    added to the stack accordingly together with the list: new_decomposition, going in depth first, just as a bkt
    algorithm. every time a full decomposition is found, former added elements are accessed from the stack with the pop
    command.
    :param n: the number that has to be decomposed in a sum of prime numbers
    :return: decompositions. a list that contains each possibility of partitioning n into prime elements
    """
    stack=[(n,[])]
    decompositions=[]
    while stack:
        num,current_decomposition=stack.pop()
        if num==0 and current_decomposition[0]!=n:
            decompositions.append(current_decomposition)
        else:
            for i in range(2, num+1):
                if its_prime(i) and i<=num:
                    new_decomposition=current_decomposition+[i]
                    stack.append((num-i,new_decomposition))

    return decompositions


def recursive(n, current_decomposition=[]):
    """
    this function implements a recursive bkt algorithm, using DFS, depth-first search. each time a new prime element is
    found, a copy of the former current_decomposition is made, and the element is added to that. the function is called
    continuously until either the sum is equal to n or the sum exceeded n, resulting in not being a correct one. each
    decomposition is stored in decompositions and returned in the end
    :param n: the number that has to be decomposed in a sum of prime elements
    :param current_decomposition: list that plays a big role during the recursive calls, helping to achieve the DFS
    :return: each decomposition is stored in the list decompositions and returned in the end
    """
    decompositions=[]
    if n==0 and len(current_decomposition)>1:
        decompositions.append(current_decomposition)
    for i in range(2, n+1):
        if its_prime(i) and i<=n:
            new_decomposition=current_decomposition.copy()
            new_decomposition.append(i)
            decompositions+= recursive(n-i, new_decomposition)
    return decompositions


def main():
    n=int(input("Insert a positive number: "))
    decompositions_recursive = recursive(n)
    if not decompositions_recursive:
        print("no possible way of decomposing", n,"as a sum of prime numbers")
    else:
        print("using the iterative method:")
        decompositions_iterative = iterative(n)
        for decomposition in decompositions_iterative:
            print(decomposition)
        print("using the recursive method:")
        for decomposition in decompositions_recursive:
            print(decomposition)

main()