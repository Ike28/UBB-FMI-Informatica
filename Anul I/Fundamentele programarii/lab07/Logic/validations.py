from Domain.bcolors import Colors
from Domain.thing import get_name, get_description, get_price, get_location, create_thing
from Logic.crud import get_by_id
from Logic.operations import get_all_rooms


def validate_id(given_id):

    if int(given_id) < 1:
        raise ValueError('\nID-ul nu poate fi mai mic decat 1.')

    return int(given_id)


def validate_price(given_price):

    if float(given_price) < 0:
        raise ValueError('\nPretul de achizitie nu poate fi un numar negativ.')

    return float(given_price)


def validate_location(given_location):

    if len(given_location) != 4:
        raise ValueError('\nLocatia data trebuie sa fie formata din exact 4 caractere.')
    if given_location == '0000':
        raise ValueError('\nLocatia data nu este permisa deoarece reprezinta un cod de sistem.')

    return given_location


def validate_terminal_command(command_as_string_list, thing_list):
    '''
    Valideaza parametrii unei comenzi introduse in terminal
    :param command_as_string_list: o lista continand handle-ul comenzii, urmat de parametri
    :param thing_list: inventarul dat
    :return: comanda transformata
    :raises: TypeError daca handle-ul comenzii nu este unul recunoscut
    '''

    erori = ''
    ready_command = []

    if command_as_string_list[0] == 'adauga':
        try:
            object_id = 0
            try:
                object_id = validate_id(command_as_string_list[1])
            except ValueError as ie:
                erori += str(ie)

            name = command_as_string_list[2]

            description = command_as_string_list[3]

            price = -1
            try:
                price = validate_price(command_as_string_list[4])
            except ValueError as pe:
                erori += str(pe)

            location = '0000'
            try:
                location = validate_location(command_as_string_list[5])
            except ValueError as le:
                erori += str(le)
            if len(erori) > 0:
                raise ValueError(erori)
            ready_command = ['adauga', object_id, name, description, price, location]
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'modifica':
        try:
            object_id = -1
            try:
                object_id = validate_id(command_as_string_list[1])
            except ValueError as ie:
                erori += str(ie)

            existing_thing = get_by_id(thing_list, object_id)
            if existing_thing is None:
                raise ValueError('\nID-ul dat nu exista in inventar.')

            name = command_as_string_list[2]
            if name == '':
                name = get_name(existing_thing)

            description = command_as_string_list[3]
            if description == '':
                description = get_description(existing_thing)

            price = command_as_string_list[4]
            if price == '':
                price = get_price(existing_thing)
            else:
                try:
                    price = validate_price(command_as_string_list[4])
                except ValueError as pe:
                    erori += str(pe)

            location = command_as_string_list[5]
            if location == '':
                location = get_location(existing_thing)
            else:
                try:
                    location = validate_location(command_as_string_list[5])
                except ValueError as le:
                    erori += str(le)
            if len(erori) > 0:
                raise ValueError(erori)
            new_thing = create_thing(object_id, name, description, price, location)
            ready_command = ['modifica', new_thing]
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'sterge':
        try:
            object_id = validate_id(command_as_string_list[1])
            ready_command = ['sterge', object_id]
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'afiseaza':
        ready_command = ['afiseaza']

    elif command_as_string_list[0] == 'mutare':
        try:
            dest, sursa = '0000', '0000'
            try:
                dest = validate_location(command_as_string_list[1])
            except ValueError as se1:
                erori += str(se1)

            try:
                sursa = validate_location(command_as_string_list[2])
            except ValueError as se2:
                erori += str(se2)

            if len(erori) > 0:
                raise ValueError(erori)

            ready_command = ['mutare', dest, sursa]
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'concat':
        try:
            string_to_add = command_as_string_list[1]
            given_price = -1
            try:
                given_price = validate_price(command_as_string_list[2])
            except ValueError as pe:
                erori += str(pe)

            if len(erori) > 0:
                raise ValueError(erori)

            ready_command = ['concat',string_to_add, given_price]
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'maxpret':
        try:
            list_rooms = get_all_rooms(thing_list)
            ready_command = ['maxpret', list_rooms]
        except Exception as ex:
            print(f'\n{Colors.YELLOW}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'ordonare':
        ready_command = ['ordonare']

    elif command_as_string_list[0] == 'sumpret':
        try:
            list_rooms = get_all_rooms(thing_list)
            ready_command = ['sumpret', list_rooms]
        except Exception as ex:
            print(f'\n{Colors.YELLOW}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')

    elif command_as_string_list[0] == 'help':
        ready_command = ['help']
    else:
        raise TypeError('\nComanda invalida:')
    return ready_command
