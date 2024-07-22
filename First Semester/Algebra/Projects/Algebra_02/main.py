n = 0
contor = 0
m = [[0] * 10 for _ in range(10)]

def is_associative():
    """
     a binary operation * on a set is associative if, for all elements a, b, and c in the set, the equation
     (a * b) * c = a * (b * c) holds true, this is why each of the 3 loops iterates for 'i', 'j' and 'k' in order to
     check whether (i*j)*k is equal to i*(j*k) or not, comparing the elements of the matrix 'm'
    :return: False if the property does not hold and True otherwise
    """
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            for k in range(1, n + 1):
                if m[m[i][j]][k] != m[i][m[j][k]]:
                    return False
    return True

def print_result(output_file):
    """
    Prints the operation table in an output file
    """
    for i in range(1, n + 1):
        print(f"(a{m[i][1]}", end="", file=output_file)
        for j in range(2, n + 1):
            print(f", a{m[i][j]}", end="", file=output_file)
        print(")", file=output_file)
    print(file=output_file)

def generate_tables(x, y, val):
    """
    The pair of numbers (x,y) symbolizes the coordinates at which the table of operation 'm' is in the current state
    and 'val' is a value from [1,n] to be placed at the position (x,y). This recursive function explores different
    combinations of values for 'val' in order to generate all possible operation tables. if it reached the end of the
    operation table, the associativity property is checked using the proper function. If the result is affirmative,
    the contor increments and the according table is printed in the output file
    """
    global contor
    m[x][y] = val
    if x == n and y == n:
        if is_associative():
            contor += 1
            with open("output5.txt", "a") as output_file:
                print_result(output_file)
        return
    """
    If the current row is at the end with index 'y' reaching the length 'n', then the next row is interrogated, else if 
    there is place to increase, 'y' will do so
    """
    if y == n:
        x += 1
        y = 1
    else:
        y += 1
    """it now explores all the remaining ways to fill the table, having 'i' iterating through a loop in range[1,n],
    recursively calling the function again and again, until having done all the combinations.(for the row values)"""
    for i in range(1, n + 1):
        generate_tables(x, y, i)


with open("input5.txt", "r") as input_file:
    n = int(input_file.readline().strip())

"""
The EXPECTED result should match the one obtained through intensive calculus. the algorithm has a time complexity of O(n^n)
, where n is the cardinal of the set, this is because for each value in the operation table, there exist n ways to
choose a possibility for a value. 
"""
with open("output5.txt", "a") as output_file:
    if int(n)==0:
        output_file.write(f"The EXPECTED number of associative operations on a set with {n} elements is 0\n")
    if int(n)==1:
        output_file.write(f"The EXPECTED number of associative operations on a set with {n} elements is 1\n")
    if int(n)==2:
        output_file.write(f"The EXPECTED number of associative operations on a set with {n} elements is 8\n")
    if int(n)==3:
        output_file.write(f"The EXPECTED number of associative operations on a set with {n} elements is 113\n")
    if int(n)==4:
        output_file.write(f"The EXPECTED number of associative operations on a set with {n} elements is 3492\n")

"""
A loop used to start generating all possible operation tables, for the first element in the operation table, having a
value from [1,n]
"""
for i in range(1, n + 1):
    generate_tables(1, 1, i)

with open("output5.txt", "a") as output_file:
    output_file.write(f"The number of associative operations on a set with {n} elements is {contor}\n")
