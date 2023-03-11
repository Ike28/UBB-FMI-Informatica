def euclidean_distance(l1, l2):
    l1[0] = float(l1[0])
    l1[1] = float(l1[1])
    l2[0] = float(l2[0])
    l2[1] = float(l2[1])

    return ((l1[0] - l2[0]) ** 2
            + (l1[1] - l2[1]) ** 2) ** (1 / 2)


def test_task1():
    location1 = [1, 5]
    location2 = [4, 1]
    res = euclidean_distance(location1, location2)
    assert res == 5.0


def runner():
    test_task1()
    l1 = input("First location:\n").strip().strip("()").split(",")
    l2 = input("Second location:\n").strip().strip("()").split(",")
    res = euclidean_distance(l1, l2)
    print("Euclidean distance: " + res.__str__())


runner()
