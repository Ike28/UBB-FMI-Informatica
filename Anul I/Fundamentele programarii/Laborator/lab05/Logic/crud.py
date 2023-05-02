from Domain.thing import create_thing, get_id
from Logic.file_management import write_file


def add_thing(thing_list, object_id, name, description, price, location):
    '''
    Adauga un obiect intr-un inventar existent
    :param thing_list: inventarul dat, lista
    :param object_id: id-ul dat
    :param name: numele dat
    :param description: descrierea data
    :param price: pretul dat
    :param location: locatia data
    :return: nu returneaza
    '''

    thing = create_thing(object_id, name, description, price, location)

    thing_list.append(thing)


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

    existing_thing = get_by_id(thing_list, del_id)
    if existing_thing is None:
        raise ValueError('\nID-ul dat nu exista!\n')
    result = []
    for ob in thing_list[::-1]:
        if get_id(ob) != del_id:
            result.append(ob)
    write_file(thing_list, filename)
    return result

