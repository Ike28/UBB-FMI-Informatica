def alfabet_hex(numar):
    '''
    Transforma un numar de 4 cifre dat in baza 2 in cifra corespondenta din baza 16
    :param numar: numarul in baza 2, string
    :return: cifra rezultata in baza 16, string
    '''

    alfabet = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    aux = numar[::-1]
    rezultat = 0
    for i in range(4):
        rezultat += (2**i)*int(aux[i])
    return alfabet[rezultat]

def test_alfabet_hex():
    assert alfabet_hex('0001') == '1'
    assert alfabet_hex('1100') == 'C'
    assert alfabet_hex('0100') == '4'
test_alfabet_hex()


def convert_to_hex(numar):
    '''
    Converteste in baza 16 un numar dat in baza 2
    :param numar: numarul in baza 2, string
    :return: rezultatul in baza 16, string
    '''

    if len(numar)%4 != 0:
        numar = '0'*(4 - len(numar)%4) + numar

    rezultat = ''

    for i in range( 0, len(numar), 4 ):
        rezultat += alfabet_hex( numar[i:i+4] )

    return rezultat

def test_convert_to_hex():
    assert convert_to_hex('1') == '1'
    assert convert_to_hex('1110') == 'E'
    assert convert_to_hex('10101011110') == '55E'
test_convert_to_hex()


def main():

    while True:
        print('Meniu')
        print('\n1 - Transformare numar din baza 2 in baza 16')
        print('X - Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == '1':
            numar_dat = input('\nIntroduceti numarul:\n')
            print('\nRezultatul este ' + convert_to_hex(numar_dat) + '\n---\n\n')
        else:
            print('\nOptiune invalida.\n---\n')

main()