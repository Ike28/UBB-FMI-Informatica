def unique_words(arr: list):
    """
    Determina cuvintele ce apar o singura data dintr-o lista de cuvinte
    :param arr: list
    :return: toate cuvintele unice continute intr-un string
    """
    counts = {}
    for word in arr:
        word = word.strip(",.!? -").lower()
        if word != "" and word in counts.keys():
            counts[word] = False
        elif word != "":
            counts[word] = True

    res = ""
    for word in counts.keys():
        if counts[word]:
            res += word + " "
    return res


def test_task4():
    sample = "ana are ana are mere rosii ana".split(" ")
    res = unique_words(sample)
    assert res == "mere rosii "


def runner():
    """
    Citeste de la tastatura un text si afiseaza cuvintele unice din el, daca exista
    :return: None
    """
    test_task4()
    arr = input("Enter input text:\n").strip().split(" ")
    if not arr:
        print("No words in given text.")
    else:
        result = unique_words(arr)
        if result == "":
            print("Every input word is repeated at least twice")
        else:
            print("Unique words in text:\n" + result)


runner()
