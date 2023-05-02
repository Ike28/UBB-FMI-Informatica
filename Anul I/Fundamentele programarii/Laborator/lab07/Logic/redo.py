from Logic.file_management import load_file, write_file


def register_redo(thing_list):
    '''
    Inregistreaza starea curenta a inventarului in stiva de REDO din redo_tree.txt
    :param thing_list: inventarul
    :return: None
    '''
    redo_list = load_file('redo_tree.txt')
    redo_list.append(thing_list)
    write_file(redo_list, 'redo_tree.txt')


def redo():
    '''
    Returneaza primul redo de facut din stiva de REDO din redo_tree.txt
    :return: starea inventarului dupa redo
    '''
    redo_list = load_file('redo_tree.txt')
    if len(redo_list) == 0:
        raise TypeError('\nNu exita modificari ulterioare!')
    return redo_list[len(redo_list) - 1]


def remove_last_in_redo():
    '''
    Actualizeaza stiva de REDO din redo_tree.txt dupa ce s-a efectuat un redo
    :return: None
    '''
    redo_list = load_file('redo_tree.txt')
    redo_list.pop()
    write_file(redo_list, 'redo_tree.txt')


def clear_redo_tree():
    '''
    Reinitializeaza stiva de REDO din redo_tree.txt ca si vida
    :return: None
    '''
    write_file([], 'redo_tree.txt')