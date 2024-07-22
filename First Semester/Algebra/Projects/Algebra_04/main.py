from collections import deque

""" 'solutions[]' stores all the valid solutions (bases) for the k-dimensional subspaces in the vector space over Z_2."""
solutions = []

""" 'solution[]' is a temporary list that gets modified during the recursive generation process. It follows the possible
bases for a k-dimensional subspace"""
solution = []

with open("input5.txt", "r") as file:
    n, k = map(int, file.readline().split())

def check(y):
    """
    x being an existing vector in the basis, and y the new vector to be added. if the XOR of x and y (working as a sum
    between 2 vectors) is smaller than y, it means adding y to the basis would NOT fulfill the property of a basis to
    be linearly independent, returning FALSE (linearly dependent, it could be written as a combination of other vectors)
    otherwise returning TRUE (the set of vectors with y included is linearly independent)
    """
    for x in solution:
        if (x ^ y) < y:
            return False
    return True


def generate_solutions(lvl):
    """
    First we check if we reached the desired dimension, that being k. (A k-dimensional subspace in the given vector
    space over Z_2), meaning that to the vector 'solutions' is appended a valid vector approved by the 'check' function
    """
    if lvl == k:
        solutions.append(list(solution))
        return

    """This loop iterates over all possible vectors i that could be added to the current solution, starting from the 
    value after the last vector in the current solution (solution[-1] + 1) to ensure that the vectors being considered
    for the next position in the basis are strictly increasing to 2^n-1
    
    If the 'check' function returns True for i, meaning it is linearly independent with all the other vectors, then
    it can be added to 'solution' and the function is called in a backtracking manner to explore the next dimension,
    lvl+1, in the basis. after the recursive call returns, 'i' is removed from the solution in order to explore all
    other possibilities of vectors without duplication"""
    for i in range(solution[-1] + 1, 1 << n):
        if check(i):
            solution.append(i)
            generate_solutions(lvl + 1)
            solution.pop()


def binary_representation(x, output_file=None):
    """ we create an empty deque (double-ended queue) in order to append efficiently elements(binary digits) at the beginning of
    the list"""
    nr = deque()

    """ we append the least significant bit of x to the left side of the deque (as bits are in reverse order compared
    to the remainders we get from the division), and we get the bit by computing 'x%2'. then we go to the following bit
    by executing 'x//2' going on until x is 0(while loop), or in other words, converting x from decimal to binary using
    multiple divisions by 2"""
    while x:
        nr.appendleft(x%2)
        x =x//2

    """Fill the remaining bits with 0 if needed"""
    while len(nr) < n:
        nr.appendleft(0)

    """display of the result"""
    output_file.write("(")
    output_file.write(str(nr[0]))
    for i in range(1, n):
        output_file.write(", " + str(nr[i]))
    output_file.write(")")

""" The following loop iterates over a range of values starting from 1 up to (2^(n-1) - 1), because we need to explore
all vectors in a binary vector space. this basically ensures that every vector COULD BE the first vector in the basis,
this possibility being proved or disproved later"""
for i in range(1, 1 << (n - 1)):
    solution.append(i)
    generate_solutions(1)
    solution.pop()

"""printing the results"""
with open("output5.txt", "w") as file:
    file.write(f"The number of {k}-dimensional subspaces of the vector space Z^{n}_2 over Z_2 is {len(solutions)}\n")
    file.write("A basis for each subspace is:\n")

    for v in solutions:
        file.write("(")
        binary_representation(v[0], file)
        for i in range(1, k):
            file.write(", ")
            binary_representation(v[i], file)
        file.write(")\n")