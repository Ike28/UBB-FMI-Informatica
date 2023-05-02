def strict_equal(list1, list2):
    '''

    :param list1:
    :param list2:
    :return:
    '''

    if len(list1) != len(list2):
        return False

    for index in list1:
        if len(list1[index]) != len(list2[index]):
            return False
        for element in list1[index]:
            if element not in list2[index]:
                return False
    return True
