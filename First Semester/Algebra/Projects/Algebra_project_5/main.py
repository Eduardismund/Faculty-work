# Given that we are working with matrices over the binary field Z_2, each row in the matrix can be represented as a
# binary number. The XOR operator is used to compare two rows by examining their binary representations bit by bit.
# If the bits at the same positions in the two rows are both 1, the result is 0.
# we use this piece of information in aiming to determine if a matrix can be written in row echelon form.
def check(y, solution):
    for x in solution:
        if x ^ y < y:
            return False
    return True
# The generate_solutions function recursively generates solutions for the matrix in reduced echelon form.
# It uses the check function to ensure that the current row can be added to the solution without destroing the row
# echelon form condition.
def generate_solutions(lvl, m, n, solution, solutions):
    if lvl == m:
        solutions.append(solution.copy())
        return

    for i in range(solution[-1], 1 << n):
        if check(i, solution):
            solution.append(i)
            generate_solutions(lvl + 1, m, n, solution, solutions)
            solution.pop()
# The binary_representation function converts a binary number x into a formatted string, representing
# the binary vector with parentheses and commas.
def binary_representation(x, n):
    binary_repr = format(x, '0' + str(n) + 'b')
    return "(" + ", ".join(binary_repr) + ")"
# The main function reads the matrix dimensions from an input file, generates solutions using the generate_solutions
# function, and writes the results to an output file.
def main(input_file, output_file):
    with open(input_file, 'r') as f:
        m, n = map(int, f.readline().split())

    solutions = []
    solution = []

    for i in range(1 << (n - 1)):
        solution.append(i)
        generate_solutions(1, m, n, solution, solutions)
        solution.pop()

    with open(output_file, 'w') as f:
        f.write(f"The number of matrices A in reduced echelon form is {len(solutions)}\n")
        f.write("The matrices are\n")

        for v in solutions:
            for i in range(len(v) - 1, -1, -1):
                f.write(binary_representation(v[i], n) + '\n')
            f.write('\n')

if __name__ == "__main__":
    main("input_5.txt", "output_5.txt")