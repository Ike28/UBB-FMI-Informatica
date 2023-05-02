from Domain.bcolors import Colors
from Domain.thing import get_location, set_location, get_price, get_description, set_description
from Logic.crud import update_thing


def change_location(thing_list, source_room, new_room):
    '''
    Muta obiectele dintr-o sala in alta, intr-un inventar dat
    :param thing_list: inventarul dat
    :param source_room: sala din care se muta
    :param new_room: sala in care se muta
    :return: inventarul modificat
    '''

    erori = ''

    source_room_list = [obiect for obiect in thing_list if get_location(obiect) == source_room]

    if len(source_room_list) == 0:
        erori += '\nSala inexistenta: Sala din care doriti sa se mute este goala.'

    if len(erori) > 0:
        raise ValueError(erori)

    for obiect in source_room_list:
        obiect = set_location(obiect, new_room)
        update_thing(thing_list, obiect)
    return thing_list


def concat_to_description_by_price(thing_list, string_to_add, given_price):
    '''
    Extinde cu string_to_add descrierea obiectelor la care pretul > given_price
    :param thing_list: inventarul dat
    :param string_to_add: sirul cu care se extinde, string
    :param given_price: pretul dupa care se compara, float
    :return: inventarul modificat
    '''

    source_room_list = [obiect for obiect in thing_list if get_price(obiect) >= given_price]

    for obiect in source_room_list:
        new_description = get_description(obiect) + string_to_add
        obiect = set_description(obiect, new_description)
        update_thing(thing_list, obiect)
    return thing_list


def get_all_rooms(thing_list):
    '''
    Furnizeaza o lista cu toate salile din inventar care nu sunt goale
    :param thing_list: inventarul dat
    :return: lista de sali
    '''

    rooms = []
    for thing in thing_list:
        if get_location(thing) not in rooms and get_location(thing) != '0000':
            rooms.append(get_location(thing))

    return rooms


def priciest_per_room(thing_list, given_room):
    '''
    Determina cel mai mare pret de achizitie dintre obiectele depozitate in given_room
    :param thing_list: inventarul dat
    :param given_room: sala in care se face determinarea
    :return: Pretul maxim cautat
    :raises: ValueError daca sala este goala
    '''

    room_inventory = [each_object for each_object in thing_list if get_location(each_object) == given_room]

    if len(room_inventory) == 0:
        raise ValueError('\nNu exista obiecte depozitate in sala data!\n')
    maximum_price = get_price(room_inventory[0])
    for ob in room_inventory:
        if get_price(ob) > maximum_price:
            maximum_price = get_price(ob)

    return maximum_price


def print_priciest(thing_list1, list_rooms):
    '''
    Afiseaza in consola pretul maxim de achizitie pentru fiecare sala din lista de sali
    :param thing_list1: inventarul dat
    :param list_rooms: lista de sali
    :return: None
    '''

    if len(list_rooms) == 0:
        raise ValueError('\nInventarul este gol!')

    for each_room in list_rooms:
        maximum_price = priciest_per_room(thing_list1, each_room)
        print(
            f'\n{Colors.LIGHT_CYAN}In sala {each_room} cel mai mare pret de achizitie este {maximum_price}.{Colors.END}')


def sort_inventory_by_price(thing_list):
    '''
    Sorteaza un inventar crescator dupa pretul de achizitie
    :param thing_list: inventarul dat
    :return: inventarul ordonat
    '''

    thing_list.sort(key=get_price)
    return thing_list


def sum_at_location(thing_list, given_location):
    '''
    Determina suma preturilor de achizitie dintr-o sala data
    :param thing_list: inventarul
    :param given_location: sala data, string
    :return: suma cautata, float
    :raises: ValueError daca nu exista obiecte in sala data
    '''

    erori = ''
    if len(given_location) != 4:
        erori += '\nLocatia data este invalida: nu este formata din 4 caractere'
    if given_location == '0000':
        erori += '\nInterogare respinsa: cod rezervat de sistem'
    sum = 0
    for element in thing_list:
        if get_location(element) == given_location:
            sum += get_price(element)
    if sum == 0:
        erori += '\nNu exista obiecte depozitate in sala data'
    if len(erori):
        raise ValueError(erori)
    return sum


def print_sums_at_locations(thing_list1, list_rooms):
    '''
    Afiseaza in consola suma preturilor de achizitie pentru fiecare sala din lista de sali
    :param thing_list1: inventarul dat
    :param list_rooms: lista de sali
    :raises: ValueError daca inventarul este gol
    :return: None
    '''

    if len(list_rooms) == 0:
        raise ValueError('\nInventarul este gol!')
    for each_room in list_rooms:
        room_sum = sum_at_location(thing_list1, each_room)
        print(f'\n{Colors.LIGHT_CYAN}In sala {each_room} suma preturilor este {room_sum}.{Colors.END}')


def remove_from_description_by_price(thing_list, string_to_remove, given_price):
    '''
    Inversa functiei de extindere a descrierii
    :param thing_list: inventarul dat
    :param string_to_remove: sirul ce se va elimina din descrieri, string
    :param given_price: pretul dupa care se compara, float
    :return: inventarul modificat
    '''

    source_room_list = [obiect for obiect in thing_list if get_price(obiect) >= given_price]

    for obiect in source_room_list:
        new_description = get_description(obiect)
        new_description = new_description[:len(new_description)-len(string_to_remove)]
        obiect = set_description(obiect, new_description)
        update_thing(thing_list, obiect)
    return thing_list
