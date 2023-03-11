from utils import *


def valid_movement(matrix, row, col, no_lines, no_cols):
    return (0 <= row < no_lines and 0 <= col < no_cols) and matrix[row][col] == 0


def flood_fill(matrix, row, col, no_lines, no_cols):
    movement_row = [-1, 0, 0, 1]
    movement_col = [0, -1, 1, 0]
    matrix[row][col] = -1

    for i in range(4):
        new_row = row + movement_row[i]
        new_col = col + movement_col[i]
        if valid_movement(matrix, new_row, new_col, no_lines, no_cols):
            flood_fill(matrix, new_row, new_col, no_lines, no_cols)


def replace_zeros(matrix, no_lines, no_cols):
    for j in range(no_cols):
        if matrix[0][j] == 0:
            flood_fill(matrix, 0, j, no_lines, no_cols)
        if matrix[no_lines - 1][j] == 0:
            flood_fill(matrix, no_lines - 1, j, no_lines, no_cols)

    for i in range(no_lines):
        if matrix[i][0] == 0:
            flood_fill(matrix, i, 0, no_lines, no_cols)
        if matrix[i][no_cols - 1] == 0:
            flood_fill(matrix, i, no_cols - 1, no_lines, no_cols)

    for i in range(no_lines):
        for j in range(no_cols):
            if matrix[i][j] == 0:
                matrix[i][j] = 1

            if matrix[i][j] == -1:
                matrix[i][j] = 0


def test_task11():
    matrix = [[1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
              [1, 0, 0, 1, 1, 0, 1, 1, 1, 1],
              [1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
              [1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
              [1, 0, 0, 1, 1, 0, 1, 1, 0, 0],
              [1, 1, 0, 1, 1, 0, 0, 1, 0, 1],
              [1, 1, 1, 0, 1, 0, 1, 0, 0, 1],
              [1, 1, 1, 0, 1, 1, 1, 1, 1, 1]]
    replace_zeros(matrix, 8, 10)
    assert matrix == [[1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
                      [1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
                      [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                      [1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
                      [1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
                      [1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
                      [1, 1, 1, 0, 1, 1, 1, 0, 0, 1],
                      [1, 1, 1, 0, 1, 1, 1, 1, 1, 1]]


def runner():
    test_task11()
    matrix, no_lines, no_cols = read_int_matrix()

    replace_zeros(matrix, no_lines, no_cols)
    print_matrix(matrix, message="Resulting matrix")


runner()
