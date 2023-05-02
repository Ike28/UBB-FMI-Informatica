from Domain.thing import get_id, get_name, get_description, get_price, get_location
from Logic.crud import get_by_id
from Logic.file_management import *


def register_undo(command, args, thing_list):
    '''
    Inregistreaza inversa unei comenzi efectuate asupra inventarului, in stiva din undo_tree.txt
    :param command: handle-ul comenzii, string
    :param args: lista de parametri
    :param thing_list: inventarul
    :return: None
    :raises: TypeError daca handle-ul comenzii nu este unul recunoscut
    '''

    undo_command = []
    if command == 'adauga':
        undo_command.append('sterge')
        undo_command.append(args[0])

    elif command == 'modifica':
        undo_command.append('modifica')
        original_thing = get_by_id(thing_list, get_id(args[0]))
        undo_command.append(original_thing)

    elif command == 'sterge':
        undo_command.append('adauga')
        deleted_thing = get_by_id(thing_list, args[0])
        undo_command.append(args[0])
        undo_command.append(get_name(deleted_thing))
        undo_command.append(get_description(deleted_thing))
        undo_command.append(get_price(deleted_thing))
        undo_command.append(get_location(deleted_thing))

    elif command == 'mutare':
        undo_command.append('mutare')
        undo_command.append(args[1])
        undo_command.append(args[0])

    elif command == 'concat':
        undo_command.append('taie')
        undo_command.append(args[0])
        undo_command.append(args[1])

    elif command == 'taie':
        undo_command.append('concat')
        undo_command.append(args[0])
        undo_command.append(args[1])

    elif command == 'ordonare':
        undo_command.append('suprascrie')
        undo_command.append(args[0])

    elif command == 'suprascrie':
        undo_command.append('ordonare')
        undo_command.append(args[0])

    else:
        raise TypeError(f'\nEroare interna: register_undo: {command} nu este o comanda valida.')
    undo_list = load_file('undo_tree.txt')
    undo_list.append(undo_command)
    write_file(undo_list, 'undo_tree.txt')


def remove_last_in_undo():
    '''
    Elimina ultima comanda din stiva de UNDO din undo_tree.txt
    :return: None
    '''

    undo_list = load_file('undo_tree.txt')
    undo_list.pop()
    write_file(undo_list, 'undo_tree.txt')


def get_undo_tree():
    '''
    Returneaza stiva de comenzi de UNDO din undo_tree.txt
    :return: stiva de comenzi, list
    '''

    undo_list = load_file('undo_tree.txt')
    return undo_list
