def e_palindromic(numar):
    '''
    Testeaza daca un numar dat este palindromic
    :param numar: numarul dat, int
    :return: True daca numar este palindromic, False altfel
    '''

    nr = str(numar)

    if nr == nr[::-1]:
        return True
    else:
        return False

def test_e_palindromic():
    assert e_palindromic(1254) == False
    assert e_palindromic(5) == True
    assert e_palindromic(12521) == True
    assert e_palindromic(10) == False
test_e_palindromic()

def lista_palindroame(lst):
    '''
    Verifica daca o lista data este formata numai din numere palindromice
    :param lst: lista data
    :return: True daca lst indeplineste proprietatea, False altfel
    '''

    for element in lst:
        if e_palindromic(element) == False:
            return False
    return True

def test_lista_palindroame():
    assert lista_palindroame([1]) == True
    assert lista_palindroame([]) == True
    assert lista_palindroame([101,3,954,7,111]) == False
    assert lista_palindroame([101,3,95459,7,111]) == True
test_lista_palindroame()

def subsecventa_maxima_palindroame(lst):
    '''
    Dintr-o lista data, determina prima subsecventa maxima formata numai din numere palindromice
    :param lst: lista data
    :return: lista rezultat reprezentand subsecventa cautata
    '''

    result = []

    for i in range(len(lst)):
        for j in range(i, len(lst)):
            if lista_palindroame(lst[i:j+1]) and (len(lst[i:j+1]) > len(result)):
                result = lst[i:j+1]
    return result

def test_subsecventa_maxima_palindroame():
    assert subsecventa_maxima_palindroame([1,5,65,98,88,101,67,111,5]) == [1,5]
    assert subsecventa_maxima_palindroame([1,5,65,98,88,101,67,111,5,96569]) == [111,5,96569]
    assert subsecventa_maxima_palindroame([1]) == [1]
    assert subsecventa_maxima_palindroame([65,94,34,700]) == []
test_subsecventa_maxima_palindroame()


def numar_biti_binar(numar):
    '''
    Calculeaza numarul de biti cu valoarea 1 din reprezentarea in baza 2 a unui numar
    :param numar: numarul dat, int
    :return: rezultatul (numarul de biti egali cu 1 din B2), int
    '''

    if numar<0:
        numar *= -1

    rezultat = 0

    while numar:
        rezultat += numar%2
        numar //= 2

    return rezultat

def test_numar_biti_binar():
    assert numar_biti_binar(0) == 0
    assert numar_biti_binar(1) == 1
    assert numar_biti_binar(15) == 4
    assert numar_biti_binar(256) == 1
test_numar_biti_binar()

def lista_numere_reprezentare_binara(lst):
    '''
    Verifica daca o lista data este formata numai din elemente cu acelasi numar de biti 1 in reprezentare binara
    :param lst: lista data
    :return: True daca lst indeplineste proprietatea, False altfel
    '''

    if lst == []:
        return True
    numar = numar_biti_binar(lst[0])

    for element in lst:
        if numar_biti_binar(element) != numar:
            return False
    return True

def test_lista_numere_reprezentare_binara():
    assert lista_numere_reprezentare_binara([]) == True
    assert lista_numere_reprezentare_binara([74]) == True
    assert lista_numere_reprezentare_binara([3,5,9,17,65]) == True
    assert lista_numere_reprezentare_binara([3,5,9,17,81]) == False
test_lista_numere_reprezentare_binara()

def subsecventa_maxima_binara(lst):
    '''
    Dintr-o lista data, determina prima subsecventa maxima formata numai din elemente cu acelasi numar de biti 1
    :param lst: lista data
    :return: lista rezultat, reprezentand subsecventa cautata
    '''

    result = []

    for i in range(len(lst)):
        for j in range(i, len(lst)):
            if lista_numere_reprezentare_binara(lst[i:j + 1]) and (len(lst[i:j + 1]) > len(result)):
                result = lst[i:j + 1]
    return result

def test_subsecventa_maxima_binara():
    assert subsecventa_maxima_binara([3,5,9,17,81]) == [3,5,9,17]
    assert subsecventa_maxima_binara([1,3,7,15,31]) == [1]
    assert subsecventa_maxima_binara([]) == []
test_subsecventa_maxima_binara()

def main():
    while True:
        print('\nMeniu')
        print('\n1 - Determina subsecventa maxima de numere palindrom')
        print('2 - Determina subsecventa maxima de numere cu acelasi numar de biti 1 in binar')
        print('X - Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == '1':
            lista = [int(elem) for elem in input('\nIntroduceti elementele listei separate prin spatiu:\n').split()]
            result = subsecventa_maxima_palindroame(lista)
            print('\nSubsecventa maxima de palindroame este ' + str(result) + '\n---\n\n')
        elif option == '2':
            lista = [int(elem) for elem in input('\nIntroduceti elementele listei separate prin spatiu:\n').split()]
            result = subsecventa_maxima_binara(lista)
            print('\nSubsecventa maxima de elemente cu acelasi numar de biti 1 este ' + str(result) + '\n---\n\n')
        else:
            print('\nOptiune invalida.\n---')
main()