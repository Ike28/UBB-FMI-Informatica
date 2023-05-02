from Domain.mysorts import MySorts


def test_my_sorted():
    lst = [1, 4, 2, 1, 3, 1000, 9, 16, 4, 2]
    assert MySorts.my_sorted(lst) == [1, 1, 2, 2, 3, 4, 4, 9, 16, 1000]
    assert MySorts.my_sorted(lst, key=lambda x: -x, reverse=True) == [1, 1, 2, 2, 3, 4, 4, 9, 16, 1000]
