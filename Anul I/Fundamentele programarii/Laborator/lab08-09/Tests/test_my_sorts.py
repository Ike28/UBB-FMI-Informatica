from Domain.mysorts import MySorts


def test_my_sorts():
    lst = [1, 5, 9, 7, 23, 4, 2]
    assert MySorts.my_sorted(lst) == [1, 2, 4, 5, 7, 9, 23]
    assert MySorts.my_sorted(lst, reverse=True) == [23, 9, 7, 5, 4, 2, 1]
    assert MySorts.my_sorted(lst, key=lambda x: -x, reverse=True) == [1, 2, 4, 5, 7, 9, 23]
    assert MySorts.my_quicksorted(lst) == [1, 2, 4, 5, 7, 9, 23]
    assert MySorts.my_quicksorted(lst, reverse=True) == [23, 9, 7, 5, 4, 2, 1]
    assert MySorts.my_quicksorted(lst, key=lambda x: -x, reverse=True) == [1, 2, 4, 5, 7, 9, 23]
