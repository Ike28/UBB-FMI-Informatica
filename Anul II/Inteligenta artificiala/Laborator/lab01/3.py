from utils import read_array


def scalar_product(first_vector: list, second_vector: list):
    if not first_vector:
        return 0
    res = 0
    for i in range(len(first_vector)):
        res += first_vector[i] * second_vector[i]
    return res


def test_task3():
    vector1 = [1, 0, 2, 0, 3]
    vector2 = [1, 2, 0, 3, 1]
    res = scalar_product(vector1, vector2)
    assert res == 4.0


def runner():
    test_task3()
    first_vector = read_array("float", "Enter first vector")
    second_vector = read_array("float", "Enter second vector")

    result = scalar_product(first_vector, second_vector)
    print("\n" + result.__str__() + " is the scalar product")


runner()
