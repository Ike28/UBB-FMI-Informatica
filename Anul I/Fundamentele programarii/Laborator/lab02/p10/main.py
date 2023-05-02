def factorial(x):
    '''
    Calculeaza factorialul unui numar dat
    :param x: numarul dat
    :return: x!
    '''
    fact = 1
    for i in range(1,x+1):
        fact *= i
    return fact

def test_factorial():
    assert factorial(1) == 1
    assert factorial(0) == 1
    assert factorial(5) == 120
test_factorial()

def combinari(n, k):
    '''
    Calculeaza numarul combinarilor de n elemente luate cate k
    :param n: cardinalul multimii asupra caruia se efectueaza combinarile
    :param k: numarul de elemente extrase intr-o combinare
    :return: numarul combinarilor
    '''

    numarator = factorial(n)
    numitor = factorial(n-k)
    numitor *= factorial(k)

    return int(numarator/numitor)

def test_combinari():
    assert combinari(5,0) == 1
    assert combinari(7,7) == 1
    assert combinari(10,6) == 210
test_combinari()

def main():

    while True:
        print('Meniu')
        print('\n1 - Combinari de n luate cate k')
        print('X - Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == '1':
            n = int(input('\nIntroduceti n:\n'))
            k = int(input('\nIntroduceti k:\n'))
            print('\nRezultatul este ' + str(combinari(n,k)) + '\n---\n\n')
        else:
            print('\nOptiune invalida.\n---\n')
main()