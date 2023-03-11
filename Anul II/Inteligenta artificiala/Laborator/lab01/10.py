from utils import *


def max_index(ordered_matrix: list, n, m):
    for j in range(0, m):
        for i in range(0, n):
            if ordered_matrix[i][j] == 1:
                return j
    return -1


def test_task10():
    matrix = [[0, 0, 0, 1, 1],
              [0, 1, 1, 1, 1],
              [0, 0, 1, 1, 1]]
    res = max_index(matrix, 3, 5)
    assert res == 1


def runner():
    test_task10()
    matrix, no_lines, no_cols = read_int_matrix()
    res = max_index(matrix, no_cols, no_lines) + 1
    if res != 0:
        print("Line " + res.__str__() + " contains most ones")
    else:
        print("No line contains ones")


runner()
