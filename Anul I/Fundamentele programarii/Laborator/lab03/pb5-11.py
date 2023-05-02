def lista_palindroame(list):
    '''
    Verifica daca o lista data are numai elemente numere palindromice
    :param list: lista data
    :return: True daca lista indeplineste proprietatea, False altfel
    '''

    for elem in list:
        if str(elem) != str(elem)[::-1]:
            return False
    return True

def test_lista_palindroame():
    assert lista_palindroame([6]) == True
    assert lista_palindroame([1,101,95459,606]) == True
    assert lista_palindroame([1,95,1]) == False
test_lista_palindroame()

def subsecv_maxima_palindroame(list):
    '''
    Dintr-o lista data, determina cea mai lunga subsecventa de numere palindromice
    :param list: lista data
    :return: lista rezultat, reprezentand subsecventa cautata
    '''

    result = []

    for i in range(len(list)):
        for j in range(i,len(list)):
            if lista_palindroame(list[i:j+1]) and len(list[i:j+1]) > len(result):
                result = list[i:j+1]
    return result

def test_subsecv_maxima_palindroame():
    assert subsecv_maxima_palindroame([]) == []
    assert subsecv_maxima_palindroame([2,3,101,95,6,7,10001,4]) == [6,7,10001,4]
    assert subsecv_maxima_palindroame([1,1,1,1,1]) == [1,1,1,1,1]
test_subsecv_maxima_palindroame()


def nr_biti1_binar(numar):
    '''
    Determina numarul de biti egali cu 1 din reprezentarea binara a unui numar intreg dat
    :param numar: numarul dat, int
    :return: numarul de biti 1 din parametrul numar, int
    '''

    nr_biti = 0
    while(numar):
        nr_biti += numar%2
        numar //= 2
    return nr_biti

def test_nr_biti1_binar():
    assert nr_biti1_binar(1) == 1
    assert nr_biti1_binar(0) == 0
    assert nr_biti1_binar(5) == 2
    assert nr_biti1_binar(2954) == 6
test_nr_biti1_binar()

def lista_nrbiti1_egali(list):
    '''
    Verifica daca o lista data este formata din numere care au la fel de multi biti 1 in binar
    :param list: lista data
    :return: True daca lista indeplineste proprietatea, False altfel
    '''

    if len(list) == 0:
        return True
    numar = nr_biti1_binar(list[0])

    for elem in list:
        if nr_biti1_binar(elem) != numar:
            return False
    return True

def test_lista_nrbiti1_egali():
    assert lista_nrbiti1_egali([5,9,17,65]) == True
    assert lista_nrbiti1_egali([1]) == True
    assert lista_nrbiti1_egali([1,2,3,4,5]) == False
    assert lista_nrbiti1_egali([]) == True
test_lista_nrbiti1_egali()


def subsecv_maxima_nrbiti1_binar(list):
    '''
    Dintr-o lista data, determina cea mai lunga subsecventa in care toate numerele au la fel de multi biti 1
    :param list: lista data
    :return: lista rezultat reprezentand subsecventa cautata
    '''

    result = []

    for i in range(len(list)):
        for j in range(i, len(list)):
            if lista_nrbiti1_egali(list[i:j+1]) and len(list[i:j + 1]) > len(result):
                result = list[i:j + 1]
    return result

def test_subsecv_maxima_nrbiti1_binar():
    assert subsecv_maxima_nrbiti1_binar([5, 9, 17, 65, 1, 5, 9, 17]) == [5,9,17,65]
    assert subsecv_maxima_nrbiti1_binar([1,1,1,1,1,1]) == [1,1,1,1,1,1]
    assert subsecv_maxima_nrbiti1_binar([]) == []
test_subsecv_maxima_nrbiti1_binar()


def concat_rezulta_numar_cifre_ord_cresc(list):
    '''
    Verifica daca o lista data ar duce la un numar cu cifre ordonate crescator prin concatenarea
    elementelor
    :param list: lista data
    :return: True daca lista indeplineste proprietatea, False altfel
    '''

    numar = ''

    for elem in list:
        numar += str(elem)
    for i in range(len(numar)-1):
        if numar[i] > numar[i+1]:
            return False
    return True

def test_concat_rezulta_numar_cifre_ord_cresc():
    assert concat_rezulta_numar_cifre_ord_cresc([1,2,3,456,799,99]) == True
    assert concat_rezulta_numar_cifre_ord_cresc([1,11, 112, 223]) == True
    assert concat_rezulta_numar_cifre_ord_cresc([]) == True
    assert concat_rezulta_numar_cifre_ord_cresc([1,95,387]) == False
test_concat_rezulta_numar_cifre_ord_cresc()


def subsecv_maxima_concat_cif_cresc(list):
    '''
    Dintr-o lista data, determina cea mai lunga subsecventa care ar duce la un numar cu cifrele in ordine
    crescatoare prin concatenarea elementelor
    :param list: lista data
    :return: lista rezultat, reprezentand subsecventa cautata
    '''

    result = []

    for i in range(len(list)):
        for j in range(i, len(list)):
            if concat_rezulta_numar_cifre_ord_cresc(list[i:j+1]) and len(list[i:j + 1]) > len(result):
                result = list[i:j + 1]
    return result

def test_subsecv_maxima_concat_cif_cresc():
    assert subsecv_maxima_concat_cif_cresc([1,2,3,98,79,99,999,9999]) == [79,99,999,9999]
    assert subsecv_maxima_concat_cif_cresc([1,1,1,1,1,2]) ==[1,1,1,1,1,2]
    assert subsecv_maxima_concat_cif_cresc([]) == []
    assert subsecv_maxima_concat_cif_cresc([5,4]) == [5]
test_concat_rezulta_numar_cifre_ord_cresc()

def main():

    lista = []
    while True:
        print('\nMeniu')
        print('A. Citire lista de numere')
        print('B. Afisare lista curenta de lucru')
        print('')
        print('1. Subsecventa maxima de palindroame')
        print('2. Subsecventa maxima de elemente cu acelasi numar de biti 1')
        print('3. Subsecventa maxima de elemente care concatenate dau un numar cu cifre crescatoare')
        print('X. Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == 'A':
            lista = [int(elem) for elem in input('\nIntroduceti elementele listei separate prin spatiu:\n').split()]
            print('\nLista memorata!\n---\n')
        elif option == 'B':
            if len(lista) == 0:
                print('\nLista curenta memorata este vida\n---\n')
            else:
                print('\nLista curenta memorata este ' + str(lista) + '\n---\n')
        elif option == '1':
            result = subsecv_maxima_palindroame(lista)
            print('\nSubsecventa maxima de palindroame este ' + str(result) + '\n---\n')
        elif option == '2':
            result = subsecv_maxima_nrbiti1_binar(lista)
            print('\nSubsecventa maxima de elemente cu acelasi numar de biti 1 este ' + str(result) + '\n---\n')
        elif option == '3':
            result = subsecv_maxima_concat_cif_cresc(lista)
            print('\nSubsecventa maxima de elemente care concatenate dau cifre in ordine crescatoare este '
                  + str(result) + '\n---\n')
        else:
            print('\nOptiune invalida\n---\n')
main()
