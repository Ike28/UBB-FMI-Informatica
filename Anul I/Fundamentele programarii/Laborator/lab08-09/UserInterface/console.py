from Service.booking_service import BookingService
from Service.cardclient_service import CardClientService
from Service.film_service import FilmService
from datetime import time, datetime, date


class Console:
    def __init__(self, film_service: FilmService, card_service: CardClientService, booking_service: BookingService):
        self.__film_service = film_service
        self.__card_service = card_service
        self.__booking_service = booking_service

    def __handle_create_film(self):
        try:
            input_id = int(input('Dati id-ul: ').strip())
            input_title = input('Dati titlul: ').strip()
            input_year = int(input('Dati anul aparitiei: ').strip())
            input_price = float(input('Dati pretul biletului: ').strip())
            input_on_screen = input('Este filmul in program? (Da/Nu): ').strip()

            if input_on_screen.lower() == 'da':
                input_on_screen = True
            else:
                input_on_screen = False

            self.__film_service.create(input_id, input_title, input_year, input_price, input_on_screen)

            print('\nFilmul a fost adaugat cu succes!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')

    def __handle_update_film(self):
        try:
            input_id = int(input('Dati id-ul: ').strip())
            input_title = input('Dati titlul (lasati gol pentru a nu schimba): ').strip()
            input_year = input('Dati anul aparitiei (lasati gol pentru a nu schimba): ').strip()
            input_price = input('Dati pretul biletului (lasati gol pentru a nu schimba): ').strip()
            input_on_screen = input('Este filmul in program? (Da/Nu) (lasati gol pentru a nu schimba): ').strip()

            if input_on_screen.lower() == 'da':
                input_on_screen = True
            elif input_on_screen.lower() != '':
                input_on_screen = False

            self.__film_service.update(input_id, input_title, input_year, input_price, input_on_screen)

            print(f'\nFilmul cu ID-ul {input_id} a fost modificat!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')

    def __handle_delete_film(self):
        try:
            input_id = int(input('Dati id-ul dupa care se sterge: ').strip())
            if self.__booking_service.check_bookings_for_film(input_id):
                raise KeyError('\nExista rezervari la acest film: Anulati mai intai rezervarile!')
            self.__film_service.delete(input_id)

            print('\nFilmul a fost sters cu succes!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')

    def __handle_read_films(self):
        films_list = self.__film_service.read()
        print()
        for each_film in films_list:
            print(f'{each_film}')
        print()

    def __handle_create_card(self):
        try:
            input_id = int(input('Dati id-ul: ').strip())
            input_surname = input('Dati numele: ').strip()
            input_name = input('Dati prenumele: ').strip()
            input_ssn = input('Dati CNP-ul: ').strip()
            read_date = input('Dati data inregistrarii (zz.ll.aaaa): ').strip().split('.')
            input_date = date(int(read_date[2]), int(read_date[1]), int(read_date[0]))
            input_points = int(input('Dati numarul de puncte acumulat: ').strip())

            self.__card_service.create(input_id, input_surname, input_name, input_ssn, input_date, input_points)

            print('\nCardul a fost adaugat cu succes!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')
        except IndexError as xe:
            print(f'\nEroare: \n{xe}\n --> reincearca!\n')

    def __handle_update_card(self):
        try:
            input_id = int(input('Dati id-ul cardului: ').strip())
            input_surname = input('Dati numele (lasati gol pentru a nu schimba): ')
            input_name = input('Dati prenumele (lasati gol pentru a nu schimba): ')
            input_ssn = input('Dati CNP-ul (lasati gol pentru a nu schimba): ')
            read_date = input('Dati data (zz:ll:aaaa) (lasati gol pentru a nu schimba): ')
            input_points = input('Dati numarul de puncte acumulate (lasati gol pentru a nu schimba): ')

            if read_date != '':
                read_date = read_date.split('.')
                input_date = date(int(read_date[2]), int(read_date[1]), int(read_date[0]))
            else:
                input_date = ''

            self.__card_service.update(input_id, input_surname, input_name, input_ssn, input_date, input_points)

            print(f'\nCardul cu ID-ul {input_id} a fost modificat!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')

    def __handle_delete_card(self):
        try:
            input_id = int(input('Dati id-ul dupa care se sterge: ').strip())
            if self.__booking_service.check_bookings_for_card(input_id):
                raise KeyError('\nClientul are mai multe rezervari: Anulati mai intai rezervarile!')
            self.__card_service.delete(input_id)

            print('\nFilmul a fost sters cu succes!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')

    def __handle_read_cards(self):
        cards_list = self.__card_service.read()
        print()
        for each_film in cards_list:
            print(each_film)
        print()

    def __handle_create_booking(self):
        try:
            input_id = int(input('Dati id-ul rezervarii: ').strip())
            input_film_id = int(input('Dati id-ul filmului: ').strip())
            input_card_id = int(input('Dati id-ul cardului de client: ').strip())
            read_date = input('Dati data rezervarii (zz.ll.aaaa): ').strip().split('.')
            input_date = date(int(read_date[2]), int(read_date[1]), int(read_date[0]))
            read_time = input('Dati ora inregistrarii (hh:mm): ').strip().split(':')
            input_time = time(int(read_time[0]), int(read_time[1]))

            points_increase = self.__booking_service.create(input_id, input_film_id, input_card_id, input_date, input_time)
            if points_increase is not None:
                client_card = self.__card_service.read_by_id(input_card_id)
                increased_points = client_card.points + points_increase
                self.__card_service.update(input_card_id, '', '', '', '', increased_points)
                print(f'\nClientul a primit un bonus de {points_increase} puncte! Acesta detine acum {increased_points} puncte.')

            print('\nRezervarea a fost adaugata cu succes!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')

    def __handle_update_booking(self):
        try:
            input_id = int(input('Dati id-ul rezervarii: ').strip())
            input_film_id = input('Dati id-ul filmului: ').strip()
            input_card_id = input('Dati id-ul cardului de client: ').strip()
            read_date = input('Dati data rezervarii (zz.ll.aaaa): ').strip()
            read_time = input('Dati ora inregistrarii (hh:mm): ').strip()

            if read_date != '':
                read_date = read_date.split('.')
                input_date = date(int(read_date[2]), int(read_date[1]), int(read_date[0]))
            else:
                input_date = ''

            if read_time != '':
                read_time = read_time.split(':')
                input_time = time(int(read_time[0]), int(read_date[1]))
            else:
                input_time = ''

            self.__booking_service.update(input_id, input_film_id, input_card_id, input_date, input_time)

            print(f'\nRezervarea cu ID-ul {input_id} a fost modificata!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n --> reincearca!\n')
        except TypeError as te:
            print(f'\nEroare: \n{te}\n --> reincearca!\n')

    def __handle_delete_booking(self):
        try:
            input_id = int(input('Dati id-ul dupa care se sterge: ').strip())
            self.__booking_service.delete(input_id)
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')

    def __handle_read_bookings(self):
        bookings_list = self.__booking_service.read()
        print()
        for each_booking in bookings_list:
            print(f'{each_booking}\n')
        print()

    def __handle_count_bookings(self):
        sorted_films_by_bookings = self.__booking_service.count_bookings()
        for each_film_id in sorted_films_by_bookings:
            print(f'REZERVARI: {sorted_films_by_bookings[each_film_id]} / ', end='')
            print(self.__film_service.read_by_id(each_film_id))

    def __handle_generate_films(self):
        try:
            films_number = int(input('Dati numarul de filme spre generare: ').strip())
            generated_list = self.__film_service.generate_films(films_number)
            for each_film in generated_list:
                print(each_film)
            print(f'\nBaza de date a fost populata cu {len(generated_list)} filme aleatorii!')
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n --> reincearca!\n')

    def __handle_full_text_search(self):
        try:
            string_to_search = input('Introduceti ce cautati: ').strip()
            if string_to_search == '':
                raise KeyError('\nSecventa de cautat este goala.')

            search_results = self.__film_service.full_search(string_to_search) + self.__card_service.full_search(string_to_search)
            if len(search_results) == 0:
                print('\nNu au fost gasite rezultate!\n')
            else:
                print(f'\nRezultatele cautarii: ({len(search_results)} matches)\n')
                for result in search_results:
                    print(result)
                print()
        except Exception as ex:
            print(f'\nEroare: \n{ex}\n --> reincearca!\n')

    def __handle_bookings_in_hour_interval(self):
        try:
            read_start = input('Dati ora de inceput (hh:mm): ').strip().split(':')
            start_hour = time(int(read_start[0]), int(read_start[1]))
            read_end = input('Dati ora de sfarsit (hh:mm): ').strip().split(':')
            end_hour = time(int(read_end[0]), int(read_end[1]))

            bookings_list = self.__booking_service.get_bookings_by_time(start_hour, end_hour)
            print()
            if len(bookings_list) == 0:
                print(f'\nNu exista rezervari intre orele {start_hour.strftime("%H:%M")}-{end_hour.strftime("%H:%M")}.')
            else:
                for each_booking in bookings_list:
                    print(each_booking)
            print()
        except Exception as ex:
            print(f'\nEroare: \n{ex}\n --> reincearca!\n')

    def __handle_cards_desc_by_points(self):
        sorted_cards = self.__card_service.sort_by_points_desc()
        print()
        if len(sorted_cards) == 0:
            print('Nu exista carduri in memorie.')
        else:
            for each_card in sorted_cards:
                print(each_card)
        print()

    def __handle_delete_bookings_in_interval(self):
        try:
            read_start = input('Dati data de inceput (zz.ll.aaaa): ').strip().split('.')
            start_day = date(int(read_start[2]), int(read_start[1]), int(read_start[0]))
            read_stop = input('Dati data de final (zz.ll.aaaa): ').strip().split('.')
            stop_day = date(int(read_stop[2]), int(read_stop[1]), int(read_stop[0]))

            deletions = self.__booking_service.delete_in_interval(start_day, stop_day)
            print()
            if deletions == 0:
                print('Nu au fost gasite rezervari in perioada precizata.')
            else:
                print(f'Au fost sterse {deletions} rezervari cu succes!')
            print()
        except Exception as ex:
            print(f'\nEroare: \n{ex}\n --> reincearca!\n')

    def __handle_birthday_bonus(self):
        try:
            read_birthday = input('Dati data de nastere dupa care se cauta (zz.ll.aaaa): ').strip().split('.')
            birth_day = date(int(read_birthday[2]), int(read_birthday[1]), int(read_birthday[0]))
            bonus_points = int(input('Dati numarul de puncte bonus aplicate: ').strip())

            birthdays = self.__card_service.apply_birthday_bonus(birth_day, bonus_points)
            print()
            if birthdays == 0:
                print('Nu au fost gasiti clienti nascuti in data precizata.')
            else:
                print(f'Au fost acordate {birthdays} bonusuri!')
            print()
        except Exception as ex:
            print(f'\nEroare: \n{ex}\n --> reincearca!\n')

    def __handle_write_films_to_excel(self):
        try:
            self.__film_service.write_films_to_excel()
            print('\nFilmele au fost exportate in films.xlsx!')
        except Exception as ex:
            print(f'\nEroare: \n{ex}\n --> reincearca!\n')

    @staticmethod
    def __print_menu():
        print('1. C.R.U.D. Filme')
        print('2. C.R.U.D. Carduri')
        print('3. C.R.U.D. Rezervari')
        print('4. Operatiuni')
        print('X. Oprire')

    def run_console(self):
        while True:
            self.__print_menu()
            option = input('\nDati comanda: ').strip()
            if option == '1':
                self.run_crud_films()
            elif option == '2':
                self.run_crud_cards()
            elif option == '3':
                self.run_crud_bookings()
            elif option == '4':
                self.run_ops_console()
            elif option == 'X':
                return
            else:
                print('\nOptiune invalida!')

    def run_crud_films(self):
        while True:
            print('A. Adaugare film')
            print('B. Modificare film')
            print('C. Stergere film')
            print('D. Afisare toate filmele')
            print('X. Inapoi')

            user_option = input('\nSelectati optiunea: ').strip()

            if user_option == 'A':
                self.__handle_create_film()
            elif user_option == 'B':
                self.__handle_update_film()
            elif user_option == 'C':
                self.__handle_delete_film()
            elif user_option == 'D':
                self.__handle_read_films()
            elif user_option == 'X':
                return
            else:
                print('\nOptiune invalida!')

    def run_crud_bookings(self):
        while True:
            print('A. Adaugare rezervare')
            print('B. Modificare rezervare')
            print('C. Stergere rezervare')
            print('D. Afisare toate rezervarile')
            print('X. Inapoi')

            user_option = input('\nSelectati optiunea: ').strip()

            if user_option == 'A':
                self.__handle_create_booking()
            elif user_option == 'B':
                self.__handle_update_booking()
            elif user_option == 'C':
                self.__handle_delete_booking()
            elif user_option == 'D':
                self.__handle_read_bookings()
            elif user_option == 'X':
                return
            else:
                print('\nOptiune invalida!')

    def run_crud_cards(self):
        while True:
            print('A. Adaugare card')
            print('B. Modificare card')
            print('C. Stergere card')
            print('D. Afisare toate cardurile')
            print('X. Inapoi')

            user_option = input('\nSelectati optiunea: ').strip()

            if user_option == 'A':
                self.__handle_create_card()
            elif user_option == 'B':
                self.__handle_update_card()
            elif user_option == 'C':
                self.__handle_delete_card()
            elif user_option == 'D':
                self.__handle_read_cards()
            elif user_option == 'X':
                return
            else:
                print('\nOptiune invalida!')

    def run_ops_console(self):
        while True:
            print('A. Afisare filme crescator dupa numarul de rezervari')
            print('B. Generare numar aleatoriu de filme')
            print('C. Cautare full text')
            print('D. Afisare rezervari dintr-un interval orar')
            print('E. Afisare carduri client descrescator dupa numarul de puncte')
            print('F. Stergere rezervari dintr-o perioada in calendar')
            print('G. Bonus aniversar')
            print('H. Exportare filme in fisier Excel')
            print('X. Inapoi')

            user_option = input('\nSelectati optiunea: ').strip()

            if user_option == 'A':	X
                self.__handle_count_bookings()
            elif user_option == 'B':
                self.__handle_generate_films()
            elif user_option == 'C':
                self.__handle_full_text_search()
            elif user_option == 'D':
                self.__handle_bookings_in_hour_interval()
            elif user_option == 'E':
                self.__handle_cards_desc_by_points()
            elif user_option == 'F':
                self.__handle_delete_bookings_in_interval()
            elif user_option == 'G':
                self.__handle_birthday_bonus()
            elif user_option == 'H':
                self.__handle_write_films_to_excel()
            elif user_option == 'X':
                return
            else:
                print('\nOptiune invalida!')

