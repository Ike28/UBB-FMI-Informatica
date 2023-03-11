from utils import *


def calculate_sums(matrix: list, no_lines: int, no_cols: int):
    sum_matrix = [[0 for _ in range(no_lines)] for _ in range(no_cols)]
    for i in range(0, no_lines):
        sum_matrix[0][i] = matrix[0][i]

    for i in range(1, no_lines):
        for j in range(0, no_cols):
            sum_matrix[i][j] = matrix[i][j] + sum_matrix[i - 1][j]

    for i in range(0, no_lines):
        for j in range(1, no_cols):
            sum_matrix[i][j] += sum_matrix[i][j - 1]

    return sum_matrix


def sub_matrix_sum(sum_matrix: list, start_pair, end_pair):
    control = 0

    sum_left_area = 0
    if start_pair[1] > 0:
        sum_left_area = sum_matrix[end_pair[0]][start_pair[1] - 1]
        control += 1
    sum_upper_area = 0
    if start_pair[0] > 0:
        sum_upper_area = sum_matrix[start_pair[0] - 1][end_pair[1]]
        control += 1
    sum_diagonal_area = 0
    if control == 2:
        sum_diagonal_area = sum_matrix[start_pair[0] - 1][start_pair[1] - 1]

    return sum_matrix[end_pair[0]][end_pair[1]] - sum_left_area - sum_upper_area + sum_diagonal_area


def test_task9():
    matrix = [[0, 2, 5, 4, 1],
              [4, 8, 2, 3, 7],
              [6, 3, 4, 6, 2],
              [7, 3, 1, 8, 3],
              [1, 5, 7, 9, 4]]
    start_pair = [1, 1]
    end_pair = [3, 3]
    sum_matrix = calculate_sums(matrix, 5, 5)
    res = sub_matrix_sum(sum_matrix, start_pair, end_pair)
    assert res == 38


def runner():
    test_task9()
    matrix, no_lines, no_cols = read_int_matrix()

    sum_matrix = calculate_sums(matrix, no_lines, no_cols)
    pairs = []
    pair = input("Enter pairs:\n").strip().split(",")
    while pair != ['']:
        pairs.append(pair)
        pair = input().strip().split(",")

    c = 0
    for p in pairs:
        c += 1
        start_pair = [int(e) for e in p[0].strip("()").split(";")]
        end_pair = [int(e) for e in p[1].strip("()").split(";")]
        res = sub_matrix_sum(sum_matrix, start_pair, end_pair)
        print("\nSum of sub-matrix #" + c.__str__() + ": " + res.__str__())


runner()
