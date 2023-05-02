def lista_nr_ord(list):
    '''

    :param list:
    :return:
    '''

    for i in range(len(list)-1):
        if list[i] > list[i+1]:
            return False

    return True

def test_lista_nr_ord():
    assert lista_nr_ord([1,2,3,4,5]) == True
    assert lista_nr_ord([]) == True
    assert lista_nr_ord([5,1,3]) == False
test_lista_nr_ord()

def subsecv_maxima_nr_ord(list):
    '''

    :param list:
    :return:
    '''

    result = []

    for i in range(len(list)):
        for j in range(i,len(list)):
            if lista_nr_ord(list[i:j+1]) and len(list[i:j+1]) > len(result):
                result = list[i:j+1]
    return result

def test_subsecv_maxima_nr_ord():
    assert subsecv_maxima_nr_ord([]) == []
    assert subsecv_maxima_nr_ord([1]) == [1]
    assert subsecv_maxima_nr_ord([1,2,3,1,5,7,8,9,10]) == [1,5,7,8,9,10]
test_subsecv_maxima_nr_ord()


def lista_ord_nr_cifre(list):
    '''

    :param list:
    :return:
    '''

    for i in range(len(list)-1):
        if len(str(list[i])) < len(str(list[i+1])):
            return False
    return True

def test_lista_ord_nr_cifre():
    assert lista_ord_nr_cifre([100,81,1]) == True
    assert lista_ord_nr_cifre([300,401,5000]) == False
test_lista_ord_nr_cifre()


def subsecv_maxima_nr_cifre_desc(list):
    '''

    :param list:
    :return:
    '''

    result = []

    for i in range(len(list)):
        for j in range(i, len(list)):
            if lista_ord_nr_cifre(list[i:j+1]) and len(list[i:j+1]) > len(result):
                result = list[i:j + 1]
    return result

def test_subsecv_maxima_nr_cifre_desc():
    assert subsecv_maxima_nr_cifre_desc([1,1,34,100,567,78,98,9]) == [100,567,78,98,9]
    assert subsecv_maxima_nr_cifre_desc([1,1,1,1,1]) == [1,1,1,1,1]
test_subsecv_maxima_nr_cifre_desc()

def main():

    while True:
        print('Meniu')
        print('1. Prop1')
        print('2. Prop2')
        print('X. Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == '1':
            lista = [int(elem) for elem in input('\nIntroduceti elementele listei separate prin spatiu:\n').split()]
            result = subsecv_maxima_nr_ord(lista)
            print('\nSubsecventa maxima de numere ordonate crescator este ' + str(result))
        elif option == '2':
            lista = [int(elem) for elem in input('\nIntroduceti elementele listei separate prin spatiu:\n').split()]
            result = subsecv_maxima_nr_cifre_desc(lista)
            print('\nSubsecventa maxima de numere cu cifre ordonate descrescator este ' + str(result))
        else:
            print('\nOptiune invalida\n')
main()