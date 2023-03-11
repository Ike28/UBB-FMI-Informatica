from utils import read_array


def repeating_val(arr: list):
    """
    Determina, dintr-un sir cu valori naturale in intervalul [1,n-1], valoarea duplicata,
    unde n este dimensiunea sirului
    :param arr: sirul de numere naturale
    :return: int
    """
    n = len(arr)
    num_sum = 0
    for i in range(0, n):
        num_sum += arr[i]
    return num_sum - (n * (n - 1)) / 2


def test_task5():
    arr = [1, 2, 3, 4, 2]
    res = repeating_val(arr)
    assert res == 2


def main():
    test_task5()
    arr = read_array("int", "Enter array")
    res = repeating_val(arr)
    print("Repeating value in array: " + res.__str__())


main()
