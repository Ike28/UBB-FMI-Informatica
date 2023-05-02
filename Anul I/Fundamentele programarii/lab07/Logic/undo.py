from Logic.file_management import load_file, write_file


def register_undo(thing_list):
    '''
    Inregistreaza starea curenta a inventarului in stiva de UNDO din undo_tree.txt
    :param thing_list: inventarul
    :return: None
    '''
    undo_list = load_file('undo_tree.txt')
    undo_list.append(thing_list)
    write_file(undo_list, 'undo_tree.txt')


def undo():
    '''
    Returneaza primul undo de facut din stiva de UNDO din undo_tree.txt
    :return: starea inventarului dupa undo
    '''
    undo_list = load_file('undo_tree.txt')
    if len(undo_list) == 0:
        raise TypeError('\nNu exista modificari anterioare!')
    return undo_list[len(undo_list) - 1]


def remove_last_in_undo():
    '''
    Actualizeaza stiva de UNDO din undo_tree.txt dupa ce s-a efectuat un undo
    :return: None
    '''
    undo_list = load_file('undo_tree.txt')
    undo_list.pop()
    write_file(undo_list, 'undo_tree.txt')
