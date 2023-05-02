from Domain.thing import get_price, get_name, get_description, get_location, to_string, create_thing
from Logic.crud import add_thing, get_by_id, update_thing, delete_thing
from copy import deepcopy

def print_menu():
    print('1. CRUD - Create, Read, Update, Delete')
    print('2. Operatiuni')
    print('3. Undo')
    print('X. Iesire')


def run_crud(thing_list):
    '''
    Ruleaza interfata meniului CRUD ce permite utilizatorului adaugare, stergere, modificare si citire a inventarului de obiecte
    :param thing_list: lista de obiecte reprezentand inventarul
    :return: lista de obiecte reprezentand inventarul modificat dupa inchiderea meniului CRUD de catre utilizator
    (asa se salveaza modificarile dorite de utilizator)
    '''

    def handle_add(thing_list1):
        '''
        Permite utilizatorului adaugarea unui obiect in inventar printr-o interfata
        :param thing_list1: lista de obiecte reprezentand inventarul in care se adauga
        :return: lista de obiecte reprezentand inventarul adaugit
        '''

        object_id = input('Dati id-ul: ')
        name = input('Dati numele: ')
        description = input('Dati descrierea: ')
        price = float(input('Dati pretul: '))
        location = input('Dati locatia depozitarii: ')

        add_thing(thing_list1, object_id, name, description, price, location)

        print('Obiectul a fost adaugat!')

    def handle_modify(thing_list1):
        '''
        Permite utilizatorului modificarea unui obiect din inventar printr-o interfata
        :param thing_list1: lista de obiecte reprezentand inventarul in care se modifica
        :return: lista de obiecte reprezentand inventarul modificat
        '''

        new_id = input('Dati id-ul: ')
        existing_thing = get_by_id(thing_list1, new_id)

        new_name = input('Dati numele (lasati gol pentru a nu se schimba): ')
        if new_name is None:
            name = get_name(existing_thing)

        new_description = input('Dati descrierea (lasati gol pentru a nu schimba): ')
        if new_description is None:
            new_description = get_description(existing_thing)

        new_price = input('Dati pretul (lasati gol pentru a nu schimba): ')
        if new_price is None:
            new_price = get_price(existing_thing)
        else:
            new_price = float(new_price)

        new_location = input('Dati locatia de depozitare (lasati gol pentru a nu schimba): ')
        if new_location is None:
            new_location = get_location(existing_thing)

        updated_thing = create_thing(new_id, new_name, new_description, new_price, new_location)
        thing_list1 = update_thing(thing_list1, updated_thing)
        print('\nObiectul a fost modificat\n---\n')
        return thing_list1

    def handle_delete(thing_list1):
        '''
        Permite utilizatorului stergerea unui obiect din inventar printr-o interfata
        :param thing_list1: lista de obiecte reprezentand inventarul din care se sterge
        :raises: ValueError daca obiectul cautat nu exista in inventar
        :return: lista de obiecte reprezentand inventarul alterat
        '''

        try:
            del_id = input('Dati id-ul de sters: ')

            new_thing_list = delete_thing(thing_list1, del_id)
            thing_list1 = deepcopy(new_thing_list)
            print('Obiectul a fost sters din memorie')
        except ValueError as ve:
            print('Eroare:', ve, ', reincearca!')
        return thing_list1

    def handle_show_all(thing_list1):
        '''
        Realizeaza afisarea intregului inventar in consola
        :param thing_list1: lista de obiecte reprezentand inventarul
        :return: nu returneaza
        '''

        if len(thing_list1) == 0:
            print('\nInventarul este gol\n---\n')
        else:
            for ob in thing_list1:
                print(to_string(ob))

    while True:
        print('-----------')
        print('A. Adaugare')
        print('B. Modificare')
        print('C. Stergere')
        print('D. Inspectare inventar')
        print('X. Inapoi')
        user_option = input('\nSelectati optiunea dorita: ')
        if user_option == 'X':
            break
        elif user_option == 'A':
            handle_add(thing_list)
        elif user_option == 'B':
            thing_list = handle_modify(thing_list)
        elif user_option == 'C':
            thing_list = handle_delete(thing_list)
        elif user_option == 'D':
            handle_show_all(thing_list)
        else:
            print('Optiune invalida')
    return thing_list


def run_console(thing_list):
    '''
    Ruleaza interfata de optiuni asupra inventarului in consola si apeleaza interfetele secundare
    :param thing_list: lista de obiecte reprezentand inventarul
    :return: nu returneaza
    '''

    while True:
        print_menu()
        user_option = input('Alegeti optiunea: ')

        if user_option == '1':
            thing_list = run_crud(thing_list)

        elif user_option == 'X':
            break
        else:
            print('Comanda invalida')
    return thing_list
