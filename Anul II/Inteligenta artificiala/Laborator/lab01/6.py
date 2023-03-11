from utils import read_array


def major_element(arr: list):
    """
    Determina elementul majoritar dintr-un sir de numere intregi
    :param arr: sirul de numere
    :return: int
    """
    n = len(arr)
    counts = {}
    for i in range(0, n):
        if arr[i] in counts.keys():
            counts[arr[i]] += 1
            if counts[arr[i]] > n / 2:
                return arr[i]
        else:
            counts[arr[i]] = 1
    return None


def test_task6():
    arr = [2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]
    res = major_element(arr)
    assert res == 2


def runner():
    test_task6()
    arr = read_array("int", "Input array")
    res = major_element(arr)
    if res is None:
        print("No element presents majority")
    else:
        print("The element of majority is " + res.__str__())


runner()
