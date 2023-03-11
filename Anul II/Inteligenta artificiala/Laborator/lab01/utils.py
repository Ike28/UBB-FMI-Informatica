def read_int_matrix():
    matrix = []
    no_lines = 0

    line = input("Enter matrix:\n").strip().strip("[],").split(",")
    no_cols = len(line)
    while line != ['']:
        no_lines += 1
        line = [int(e) for e in line]
        matrix.append(line)
        line = input().strip().strip("[],").split(",")

    return matrix, no_lines, no_cols


def read_array(type: str, message: str):
    if type == "int":
        result = [int(e) for e in input(message + ":\n").strip().strip("[]").split(",")]
    elif type == "float":
        result = [float(e) for e in input(message + ":\n").strip().strip("[]").split(",")]
    else:
        result = input(message + ":\n").strip().strip("[]").split(",")

    return result


def print_matrix(matrix: list, message: str):
    print("\n" + message + ":")
    for row in matrix:
        print(row)
