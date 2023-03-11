from utils import read_array


def kth_biggest(arr: list, k: int):
    return sorted(arr)[-k]


def test_task7():
    k = 2
    arr = [7, 4, 6, 3, 9, 1]
    res = kth_biggest(arr, k)
    assert res == 7


def runner():
    test_task7()
    arr = read_array("int", "Input array")
    k = int(input("k = ").strip())
    result = kth_biggest(arr, k)
    print("\n" + k.__str__() + "th biggest element is: " + result.__str__())


runner()
