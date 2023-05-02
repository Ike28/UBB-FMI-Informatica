from Domain.thing import get_price, get_name, get_description, get_location, create_thing
from Logic.crud import add_thing, get_by_id, update_thing, delete_thing, show_all
from copy import deepcopy
from Domain.bcolors import Colors
from Logic.operations import change_location, concat_to_description_by_price, get_all_rooms, \
    sort_inventory_by_price, print_priciest, print_sums_at_locations
from Logic.undo import register_undo, remove_last_in_undo, undo
from Logic.redo import register_redo, remove_last_in_redo, redo, clear_redo_tree
from Logic.terminal_ops import handle_command
from Logic.validations import validate_id,validate_location,validate_price


def print_menu():
    print('\n-----------')
    print('Meniu principal')
    print('-----------')
    print('1. CRUD - Create, Read, Update, Delete')
    print('2. Operatiuni')
    print('3. Undo')
    print('4. Redo')
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

        try:
            object_id = input('Dati id-ul: ')
            name = input('Dati numele: ')
            description = input('Dati descrierea: ')
            price = input('Dati pretul: ')
            location = input('Dati locatia depozitarii: ')

            object_id = validate_id(object_id)
            price = validate_price(price)
            location = validate_location(location)

            backup = deepcopy(thing_list1)

            add_thing(thing_list1, object_id, name, description, price, location)

            print(f'\n  {Colors.LIGHT_GREEN}Obiectul a fost adaugat!{Colors.END}')
            register_undo(backup)
            clear_redo_tree()
        except Exception as ex:
            print(f'\n{Colors.YELLOW}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')

    def handle_modify(thing_list1):
        '''
        Permite utilizatorului modificarea unui obiect din inventar printr-o interfata
        :param thing_list1: lista de obiecte reprezentand inventarul in care se modifica
        :return: lista de obiecte reprezentand inventarul modificat
        '''

        try:
            new_id = int(input('Dati id-ul: '))
            existing_thing = get_by_id(thing_list1, new_id)
            if existing_thing is None:
                raise TypeError('\nID-ul dat nu exista in inventar.')

            new_name = input('Dati numele (lasati gol pentru a nu se schimba): ')
            if new_name == '':
                new_name = get_name(existing_thing)

            new_description = input('Dati descrierea (lasati gol pentru a nu schimba): ')
            if new_description == '':
                new_description = get_description(existing_thing)

            new_price = float(input('Dati pretul (lasati gol pentru a nu schimba): '))
            if new_price == '':
                new_price = get_price(existing_thing)
            else:
                new_price = validate_price(new_price)

            new_location = input('Dati locatia de depozitare (lasati gol pentru a nu schimba): ')
            if new_location == '':
                new_location = get_location(existing_thing)
            else:
                new_location = validate_location(new_location)

            updated_thing = create_thing(new_id, new_name, new_description, new_price, new_location)

            backup = deepcopy(thing_list1)

            thing_list1 = update_thing(thing_list1, updated_thing)
            print(f'\n  {Colors.LIGHT_GREEN}Obiectul a fost modificat!{Colors.END}')

            register_undo(backup)
            clear_redo_tree()
        except Exception as ex:
            print(f'\n{Colors.YELLOW}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    def handle_delete(thing_list1):
        '''
        Permite utilizatorului stergerea unui obiect din inventar printr-o interfata
        :param thing_list1: lista de obiecte reprezentand inventarul din care se sterge
        :raises: ValueError daca obiectul cautat nu exista in inventar
        :return: lista de obiecte reprezentand inventarul alterat
        '''

        try:
            del_id = int(input('Dati id-ul de sters: '))
            del_id = validate_id(del_id)

            existing_thing = get_by_id(thing_list, del_id)
            if existing_thing is None:
                raise ValueError('\nID-ul dat nu exista in inventar!\n')

            backup = deepcopy(thing_list1)

            new_thing_list = delete_thing(thing_list1, del_id)
            thing_list1 = deepcopy(new_thing_list)
            print(f'\n  {Colors.LIGHT_GREEN}Obiectul a fost sters din memorie!{Colors.END}')

            register_undo(backup)
            clear_redo_tree()
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    def handle_show_all(thing_list1):
        '''
        Realizeaza afisarea intregului inventar in consola
        :param thing_list1: lista de obiecte reprezentand inventarul
        :return: nu returneaza
        '''

        thing_list1 = show_all(thing_list1)
        return thing_list1

    while True:
        print('\n-----------')
        print('C.R.U.D.')
        print('-----------')
        print('A. Adaugare')
        print('B. Modificare')
        print('C. Stergere')
        print('D. Inspectare inventar')
        print('X. Inapoi')
        user_option = input(f'\n  {Colors.DARK_GRAY}Selectati optiunea dorita: {Colors.END}')
        if user_option == 'X':
            break
        elif user_option == 'A':
            handle_add(thing_list)
        elif user_option == 'B':
            thing_list = handle_modify(thing_list)
        elif user_option == 'C':
            thing_list = handle_delete(thing_list)
        elif user_option == 'D':
            thing_list = handle_show_all(thing_list)
        else:
            print(f'\n  {Colors.LIGHT_RED}Optiune invalida{Colors.END}')
    return thing_list


def run_operations(thing_list):
    '''
    Ruleaza interfata meniului de operatiuni suplimentare in consola
    :param thing_list: inventarul dat
    :return: inventarul in care s-au salvat modificarile efectuate prin operatiuni
    '''

    def handle_move(thing_list1):
        '''
        Permite utilizatorului mutarea inventarului unei sali in alta sala printr-o interfata
        :param thing_list1: inventarul dat
        :return: inventarul modificat
        '''

        try:
            source_room = input('\nDati sala din care se muta: ')
            destination_room = input('\nDati sala in care se muta: ')

            source_room = validate_location(source_room)
            destination_room = validate_location(destination_room)

            backup = deepcopy(thing_list1)

            thing_list1 = change_location(thing_list1, source_room, destination_room)
            register_undo(backup)
            clear_redo_tree()
            print(f'\n{Colors.LIGHT_GREEN}Toate obiectele din {source_room} au fost mutate in {destination_room}.{Colors.END}')
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    def handle_concat(thing_list1):
        '''
        Permite utilizatorului extinderea descrierii obiectelor din inventar printr-o interfata
        :param thing_list1: inventarul dat
        :return: inventarul modificat
        '''

        try:
            search_price = int(input('\nDati pretul dupa care se compara: '))
            search_price = validate_price(search_price)
            added_string = input('\nDati sirul de adaugat la descriere: ')

            backup = deepcopy(thing_list1)
            thing_list1 = concat_to_description_by_price(thing_list1, added_string, search_price)
            print(f'\n{Colors.LIGHT_GREEN}Descrierea obiectelor a fost extinsa.{Colors.END}')
            register_undo(backup)
            clear_redo_tree()
        except Exception as ex:
            print(f'\n{Colors.YELLOW}Eroare: \n{ex}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    def handle_get_priciest_list(thing_list1):
        '''
        Permite utilizatorului afisarea pretului maxim per sala printr-o interfata
        :param thing_list1: inventarul dat
        :return: inventarul modificat
        '''

        list_rooms = get_all_rooms(thing_list1)

        try:
            print_priciest(thing_list1, list_rooms)
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    def handle_sort_by_price(thing_list1):
        '''
        Permite utilizatorului sortarea crescatoare a inventarului dupa pret printr-o interfata
        :param thing_list1: inventarul dat
        :return: inventarul modificat
        '''

        backup = deepcopy(thing_list1)

        thing_list1 = sort_inventory_by_price(thing_list1)
        print(f'\n{Colors.LIGHT_GREEN}Inventarul a fost ordonat dupa preturile de achizitie a obiectelor.{Colors.END}')

        register_undo(backup)
        clear_redo_tree()
        return thing_list1

    def handle_price_sum_for_each_location(thing_list1):
        '''
        Permite utilizatorului afisarea sumei preturilor per sala printr-o interfata
        :param thing_list1: inventarul dat
        :return: inventarul modificat
        '''

        list_rooms = get_all_rooms(thing_list1)

        try:
            print_sums_at_locations(thing_list1, list_rooms)
        except ValueError as ve:
            print(f'\n{Colors.YELLOW}Eroare: \n{ve}\n --> reincearca!{Colors.END}\n')

    while True:
        print('\n-----------')
        print('Operatiuni')
        print('-----------')
        print('A. Mutare obiecte dintr-o sala in alta')
        print('B. Extindere descriere a unui obiect daca pretul acestuia este mai mare decat unul introdus')
        print('C. Determinare cel mai mare pret pentru fiecare sala')
        print('D. Ordonarea inventarului crescator dupa pretul de achizitie')
        print('E. Afisarea sumei preturilor pentru fiecare sala')
        print('X. Inapoi')
        user_option = input(f'\n  {Colors.DARK_GRAY}Selectati optiunea dorita: {Colors.END}')
        if user_option == 'X':
            break
        elif user_option == 'A':
            thing_list = handle_move(thing_list)
        elif user_option == 'B':
            thing_list = handle_concat(thing_list)
        elif user_option == 'C':
            handle_get_priciest_list(thing_list)
        elif user_option == 'D':
            thing_list = handle_sort_by_price(thing_list)
        elif user_option == 'E':
            handle_price_sum_for_each_location(thing_list)
        else:
            print(f'\n  {Colors.LIGHT_RED}Optiune invalida{Colors.END}')
    return thing_list


def run_console(thing_list):
    '''
    Ruleaza interfata de optiuni asupra inventarului in consola si apeleaza interfetele secundare
    :param thing_list: inventarul dat
    :return: inventarul modificat
    '''

    # TODO : de adaugat undo/redo in fiecare meniu

    def handle_undo(thing_list1):
        try:
            backup = deepcopy(thing_list1)
            thing_list1 = undo()
            remove_last_in_undo()
            register_redo(backup)
            print(f'\n  {Colors.LIGHT_GREEN}Ultima modificare a fost anulata!{Colors.END}')
        except TypeError as te:
            print(f'\n{Colors.YELLOW}Eroare: \n{te}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    def handle_redo(thing_list1):
        try:
            backup = deepcopy(thing_list1)
            thing_list1 = redo()
            remove_last_in_redo()
            register_undo(backup)
            print(f'\n  {Colors.LIGHT_GREEN}Urmatoarea modificare a fost reefectuata!{Colors.END}')
        except TypeError as te:
            print(f'\n{Colors.YELLOW}Eroare: \n{te}\n --> reincearca!{Colors.END}\n')
        return thing_list1

    while True:
        print_menu()
        user_option = input(f'\n  {Colors.DARK_GRAY}Selectati optiunea dorita: {Colors.END}')

        if user_option == '1':
            thing_list = run_crud(thing_list)
        elif user_option == '2':
            thing_list = run_operations(thing_list)
        elif user_option == '3':
            thing_list = handle_undo(thing_list)
        elif user_option == '4':
            thing_list = handle_redo(thing_list)
        elif user_option == 'X':
            break
        else:
            print(f'\n  {Colors.LIGHT_RED}Optiune invalida{Colors.END}')
    return thing_list
