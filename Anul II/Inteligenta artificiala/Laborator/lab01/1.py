def last_word(arr: list):
    """
    Returneaza ultimul cuvant alfabetic dintr-o lista de cuvinte
    :param arr: lista de cuvinte, list
    :return: cuvantul cautat, string
             None daca nu au fost gasite cuvinte
    """
    if not arr:
        return None

    last = arr[0].strip(",.!? -")
    for each_word in arr[1:]:
        each_word = each_word.strip(",.!? -")
        if (each_word != "") and (each_word >= last):
            last = each_word
    if last == "":
        return None
    return last


def test_task1():
    arr = "Ana are mere rosii si galbene".split(" ")
    res = last_word(arr)
    assert res == "si"


def runner():
    """
    Citeste de la tastatura un text si afiseaza ultimul cuvant alfabetic din el
    :return: None
    """
    test_task1()
    arr = input("Enter input text:\n").strip().split(" ")
    result = last_word(arr)
    if result is None:
        print("No words in given text")
    else:
        print("Last alphabetic word is \"" + result + "\"")


runner()
