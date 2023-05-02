from Service.city_service import CityService
from Service.street_service import StreetService


class Console:
    def __init__(self, city_service: CityService, street_service: StreetService):
        self.__city_service = city_service
        self.__street_service = street_service

    def __handle_add_city(self):
        try:
            given_id = input('Dati id-ul: ').strip()
            given_name = input('Dati numele orasului: ').strip()
            given_population = input('Dati populatia orasului: ').strip()
            self.__city_service.create(given_id, given_name, given_population)
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n--->reincearca!')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n--->reincearca!')

    def __handle_read_cities(self):
        cities_list = self.__city_service.read()
        for each_city in cities_list:
            print(each_city)

    def __handle_add_street(self):
        try:
            given_id = input('Dati id-ul: ').strip()
            given_city_id = input('Dati id-ul orasului: ').strip()
            given_name = input('Dati numele strazii: ').strip()
            given_length = input('Dati lungimea strazii: ').strip()
            self.__street_service.create(given_id, given_city_id, given_name, given_length)
        except KeyError as ke:
            print(f'\nEroare: \n{ke}\n--->reincearca!')
        except ValueError as ve:
            print(f'\nEroate: \n{ve}\n--->reincearca!')

    def __handle_read_streets(self):
        streets_list = self.__street_service.read()
        for each_street in streets_list:
            print(each_street)

    def __handle_dump_cities_to_file(self):
        filename = self.get_file_name('Dati numele fisierului: ')
        self.__city_service.dump_cities(filename)

    @staticmethod
    def __print_menu():
        print('1. Adaugare oras')
        print('2. Adaugare strada')
        print('3. Afisare orase')
        print('4. Afisare strazi')
        print('5. Orase in JSON')
        print('X. Oprire')

    def run_interface(self):
        while True:
            self.__print_menu()

            option = input('\nSelectati optiunea dorita: ').strip()

            if option == '1':
                self.__handle_add_city()
            elif option == '2':
                self.__handle_add_street()
            elif option == '3':
                self.__handle_read_cities()
            elif option == '4':
                self.__handle_read_streets()
            elif option == '5':
                self.__handle_dump_cities_to_file()
            elif option == 'X':
                return
            else:
                print('\nOptiune invalida!\n')

    @staticmethod
    def get_file_name(filename_specifier: str):
        while True:
            try:
                filename = input(filename_specifier).strip()
                if filename == '':
                    raise KeyError('\nNumele nu poate fi gol.')
                return f'{filename}.txt'
            except KeyError as ke:
                print(f'Eroare: {ke}\n--->reincearca!')
