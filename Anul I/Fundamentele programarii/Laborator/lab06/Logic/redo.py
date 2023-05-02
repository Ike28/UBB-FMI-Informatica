from Domain.thing import get_name, get_description, get_price, get_location, get_id
from Logic.crud import get_by_id
from Logic.file_management import load_file, write_file


def register_redo(undo_command, thing_list):
    '''
    Inregistreaza inversa unei comenzi de UNDO in stiva de comenzi de REDO din redo_tree.txt
    :param undo_command: comanda de UNDO data
    :param thing_list: inventarul dat
    :return: None
    :raises: TypeError cand comanda data nu este una recunoscuta
    '''

    redo_command = []
    if undo_command[0] == 'adauga':
        redo_command.append('sterge')
        redo_command.append(undo_command[1])

    elif undo_command[0] == 'modifica':
        redo_command.append('modifica')
        original_thing = get_by_id(thing_list, get_id(undo_command[1]))
        redo_command.append(original_thing)

    elif undo_command[0] == 'sterge':
        redo_command.append('adauga')
        deleted_thing = get_by_id(thing_list, undo_command[1])
        redo_command.append(undo_command[1])
        redo_command.append(get_name(deleted_thing))
        redo_command.append(get_description(deleted_thing))
        redo_command.append(get_price(deleted_thing))
        redo_command.append(get_location(deleted_thing))

    elif undo_command[0] == 'mutare':
        redo_command.append('mutare')
        redo_command.append(undo_command[2])
        redo_command.append(undo_command[1])

    elif undo_command[0] == 'concat':
        redo_command.append('taie')
        redo_command.append(undo_command[1])
        redo_command.append(undo_command[2])

    elif undo_command[0] == 'taie':
        redo_command.append('concat')
        redo_command.append(undo_command[1])
        redo_command.append(undo_command[2])

    elif undo_command[0] == 'ordonare':
        redo_command.append('suprascrie')
        redo_command.append(undo_command[1])

    elif undo_command[0] == 'suprascrie':
        redo_command.append('ordonare')
        redo_command.append(undo_command[1])

    else:
        raise TypeError(f'\nEroare interna: register_redo: {undo_command[0]} nu este o comanda valida.')
    redo_list = load_file('redo_tree.txt')
    redo_list.append(redo_command)
    write_file(redo_list, 'redo_tree.txt')


def remove_last_in_redo():
    '''
    Sterge ultima comanda de REDO adaugata in redo_tree.txt
    :return: None
    '''

    redo_list = load_file('redo_tree.txt')
    redo_list.pop()
    write_file(redo_list, 'redo_tree.txt')


def get_redo_tree():
    '''
    Returneaza stiva de comenzi de REDO din redo_tree.txt
    :return: stiva de comenzi, list
    '''

    redo_list = load_file('redo_tree.txt')
    return redo_list


def clear_redo_tree():
    '''
    Goleste stiva de REDO din redo_tree.txt
    :return: None
    '''

    write_file([], 'redo_tree.txt')
