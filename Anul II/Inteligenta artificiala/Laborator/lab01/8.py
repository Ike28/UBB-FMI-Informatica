from queue import Queue


def generate_binary_values_up_to(upper_limit: int):
    binary_code = Queue()
    binary_code.put("1")

    result = []
    for _ in range(upper_limit):
        next_value = binary_code.get()
        result.append(next_value)
        binary_code.put(next_value + "0")
        binary_code.put(next_value + "1")

    return result


def test_task8():
    limit = 4
    res = generate_binary_values_up_to(limit)
    assert res == ["1", "10", "11", "100"]


def runner():
    test_task8()
    upper_limit = int(input("Enter interval limit:\n").strip())
    result = generate_binary_values_up_to(upper_limit)
    print("\nBinary numbers from 1 to " + upper_limit.__str__() + ":")
    for value in result:
        print(value)


runner()
