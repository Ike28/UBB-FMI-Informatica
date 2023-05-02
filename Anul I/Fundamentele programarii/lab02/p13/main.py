def convert_to_fahrenheit(temp, base):
    '''
    Transforma o temperatura dintr-o scara data in scara Fahrenheit
    :param temp: temperatura data, float
    :param base: scara initiala, string ('C', 'F' sau 'K')
    :return: temperatura in grade F, float
    '''

    if base == 'C':
        return temp * 1.8 + 32
    elif base == 'K':
        return temp * 1.8 - 459.67
    else:
        return temp

def test_convert_to_fahrenheit():
    assert convert_to_fahrenheit(0,'K') == -459.67
    assert convert_to_fahrenheit(0,'C') == 32.0
test_convert_to_fahrenheit()

def convert_to_celsius(temp, base):
    '''
    Transforma o temperatura dintr-o scara data in scara Celsius
    :param temp: temperatura data, float
    :param base: scara initiala, string ('C, 'F' sau 'K')
    :return: temperatura in grade C, float
    '''

    if base == 'F':
        return (temp - 32) / 1.8
    elif base == 'K':
        return temp - 273.15
    else:
        return temp

def test_convert_to_celsius():
    assert convert_to_celsius(0,'K') == -273.15
    assert convert_to_celsius(0,'F') == -17.77777777777778
    assert convert_to_celsius(32,'F') == 0.0
test_convert_to_celsius()

def convert_to_kelvin(temp, base):
    '''
    Transforma o temperatura dintr-o scara data in scara Kelvin
    :param temp: temperatura data, float
    :param base: scara initiala, string ('C', 'F' sau 'K')
    :return: temperatura in grade K, float
    '''

    if base == 'C':
        return temp + 273.15
    elif base == 'F':
        return (temp + 459.67) / 1.8
    else:
        return temp

def test_convert_to_kelvin():
    assert convert_to_kelvin(0,'C') == 273.15
    assert convert_to_kelvin(100,'C') == 373.15
test_convert_to_kelvin()


def main():

    while True:
        print('\nMeniu')
        print('\n1 - Transformari de temperatura')
        print('X - Oprire\n')
        option = input()
        if option == 'X':
            break
        elif option == '1':
            temperature = float(input('\nIntroduceti temperatura:\n'))
            scale1 = input('Introduceti scara sursa (C, F sau K):\n')
            scale2 = input('Introduceti scara pentru rezultat (C, F sau K):\n')
            if scale2 == 'C':
                result = convert_to_celsius(temperature, scale1)
            elif scale2 == 'F':
                result = convert_to_fahrenheit(temperature, scale1)
            else:
                result = convert_to_kelvin(temperature, scale1)
            print('\nRezultatul este ' + str(result) + u"\N{DEGREE SIGN}" + scale2 + '\n---\n\n')
        else:
            print('\nOptiune invalida.\n---\n')
main()