from Domain.bcolors import Colors
from Domain.thing import create_thing, get_id, to_string
from Logic.file_management import write_file, load_file


def add_thing(thing_list, object_id, name, description, price, location, filename='thing_list.txt'):
    '''
    Adauga un obiect intr-un inventar existent
    :param thing_list: inventarul dat, lista
    :param object_id: id-ul dat
    :param name: numele dat
    :param description: descrierea data
    :param price: pretul dat
    :param location: locatia data
    :param filename: fisierul in care se scrie inventarul adaugit
    :return: inventarul adaugit
    '''

    # erori = ''
    #
    # if location == '0000':
    #     erori += '\nLocatia data este invalida deoarece reprezinta un cod de sistem.'
    # if object_id < 1:
    #     erori += '\nID-ul nu poate fi mai mic decat 1.'
    # if len(location) != 4:
    #     erori += '\nLocatia data trebuie sa fie formata din exact 4 caractere.'
    # if price < 0:
    #     erori += '\nPretul de achizitie nu poate fi un numar negativ.'
    #
    # if len(erori) > 0:
    #     raise ValueError(erori)

    thing = create_thing(object_id, name, description, price, location)
    thing_list.append(thing)
    write_file(thing_list, filename)
    return thing_list


def get_by_id(thing_list, object_id):
    '''
    Cauta in inventar obiectul dupa id
    :param thing_list: inventarul de obiecte, lista
    :param object_id: id-ul dupa care se cauta
    :return: obiectul cautat daca exista/None altfel
    '''

    for ob in thing_list:
        if get_id(ob) == object_id:
            return ob

    return None


def update_thing(thing_list, new_thing, filename='thing_list.txt'):
    '''
    Modifica un obiect din inventar prin inlocuirea cu unul echivalent
    :param thing_list: inventarul de obiecte, lista
    :param new_thing: noul obiect echivalent
    :param filename: inventarul rezultat se va suprascrie in fisierul filename
    :return: inventarul modificat
    '''

    result = [existing_thing for existing_thing in thing_list if get_id(existing_thing) != get_id(new_thing)] + [new_thing]
    write_file(result, filename)
    return result


def delete_thing(thing_list, del_id, filename='thing_list.txt'):
    '''
    Sterge un obiect din inventarul memorat dupa id
    :param thing_list: inventarul de obiecte, lista
    :param del_id: id-ul obiectului de sters
    :param filename: inventarul rezultat se va suprascrie in fisierul filename
    :return: inventarul modificat
    :raises: ValueError daca nu exista obiectul cu id-ul dat
    '''

    result = []
    for ob in thing_list[::-1]:
        if get_id(ob) != del_id:
            result.append(ob)
    write_file(thing_list, filename)
    return result


def show_all(thing_list1):
    '''
    Afiseaza un inventar dupa formula din Domain.thing.to_str
    :param thing_list1: inventarul dat
    :return: None
    '''

    list_to_print = [each_object for each_object in thing_list1 if get_id(each_object) != 0]

    if len(list_to_print) == 0:
        print(f'\n  {Colors.BROWN}Inventarul este gol.{Colors.END}')
    else:
        for ob in list_to_print:
            print(to_string(ob))
    return thing_list1


def override_list(thing_list1, new_list):
    '''
    Suprascrie in fisierul thing_list.txt
    :param thing_list1: inventarul initial (placeholder - necesar pentru functionarea UNDO/REDO)
    :param new_list: noul inventar cu care se suprascrie
    :return: inventarul nou
    '''

    write_file(new_list)
    thing_list1 = load_file()
    return thing_list1
