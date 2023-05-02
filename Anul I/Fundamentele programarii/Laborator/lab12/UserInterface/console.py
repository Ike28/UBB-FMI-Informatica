from Service.artist_service import ArtistService
from Service.painting_service import PaintingService


class Console:
    """
    Defineste o interfata cu utilizatorul pentru servicii de functionalitati relationand intre tablouri si pictori
    """
    def __init__(self, artist_service: ArtistService, painting_service: PaintingService):
        """
        Creeaza interfata cu utilizatorul pentru functionalitati pe baza de obiecte tablou si pictor
        :param artist_service: serviciu de functionalitati pentru obiectele pictor, obiect ArtistService
        :param painting_service: serviciu de functionalitati pentru obiecte tablou, obiect PaintingService
        """
        self.__artist_service = artist_service
        self.__painting_service = painting_service

    @staticmethod
    def __print_menu():
        """
        Listeaza in consola utilizatorului meniul de functionalitati
        :return: None
        """
        print('\n--------------')
        print('1. Adaugare pictor')
        print('   a.Afisare pictori')
        print('2. Adaugare tablou')
        print('   b.Afisare tablouri')
        print('3. Afisare cel mai scump tablou per stil')
        print('4. Afisare pictori descrescator dupa numarul de tablouri realizate dupa un an dat')
        print('5. Exportare pictori cu tablouri in fisier JSON')
        print('x. Oprire')
        print('-------------\n')

    def __handle_add_artist(self):
        """
        Permite utilizatorului sa insereze un pictori.
        Utilizatorul va insera ID-ul, numele si stilul operelor sale.
        :return:
        """
        try:
            input_id = input('Dati id-ul pictorului: ').strip()
            input_name = input('Dati numele pictorului: ').strip()
            input_style = input('Dati stilul operelor sale (clasic, modern sau abstract): ').strip()

            self.__artist_service.create(input_id, input_name, input_style)
            print('\nPictorul a fost inregistrat!')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n--->reincearca!')

    def __handle_read_artists(self):
        """
        Permite utilizatorului sa verifice ce pictori a inserat.
        Daca nu-i convin ii poate sterge din fisierul artists.txt:
        Pentru ai sterge - Ctrl+A+Delete
        :return: None
        """
        artist_list = self.__artist_service.read()
        if len(artist_list) == 0:
            print('\nNu au fost gasiti pictori inregistrati.')
        else:
            print()
            for artist in artist_list:
                print(artist)
            print()

    def __handle_add_painting(self):
        """
        Permite ulizatorului sa insereze un tablou.
        Utilizatorul va insera ID-ul tabloului, ID-ul pictorului, pretul si anul realizarii.

        :return: None
        """
        try:
            input_id = input('Dati id-ul tabloului: ').strip()
            input_artist_id = input('Dati id-ul autorului: ').strip()
            input_title = input('Dati titlul tabloului: ').strip()
            input_price = input('Dati pretul tabloului: ').strip()
            input_year = input('Dati anul in care a fost pictat: ').strip()

            self.__painting_service.create(input_id, input_artist_id, input_title, input_price, input_year)
            print('\nTabloul a fost inregistrat!')
        except ValueError as ve:
            print(f'\nEroare: \n{ve}\n--->reincearca!')

    def __handle_read_paintings(self):
        """
        Permite utilizatorului sa verifice ce tablouri a inserat.
        Daca nu-i convin ii poate sterge din fisierul paintings.txt:
        Pentru ai sterge - Ctrl+A+Delete

        :return:
        """
        painting_list = self.__painting_service.read()
        if len(painting_list) == 0:
            print('\nNu au fost gasite tablouri inregistrate.')
        else:
            print()
            for painting in painting_list:
                print(self.__painting_service.to_str(painting))
                print()
            print()

    def __handle_sort_artists_by_paintings(self):
        """
        Permite utilizatorului sa vada ca pictorii ordonati descrescator dupa numarul
        de tablori realizate
        :return: None
        """
        try:
            input_year = int(input('Dati anul de inceput al realizarii tablourilor: '))
            sorted_artists = self.__painting_service.get_artists_by_number_of_paintings(input_year)
            if sorted_artists == {}:
                print('\nNu au fost gasiti pictori inregistrati.')
            else:
                for each_id in sorted_artists.keys():
                    print(f'TABLOURI: {sorted_artists[each_id]}\n--->{self.__artist_service.read_by_id(each_id)}')
        except ValueError:
            print('\nEroare: \n\nAnul dat nu este un numar.\n--->reincearca!')

    def __export_json(self):
        """
        Permite utilizatorului sa exporte intr-un fisier cu extensie .json pictorii si tablourile
        realizate de ei.
        :return: None
        """
        while True:
            filename = input('Introduceti numele fisierului JSON pentru creare:').strip()
            if filename != '':
                break
            else:
                print('\nEroare:\n\nNumele fisierului trebuie sa contina macar o cifra sau o litera.\n--->reincearca!\n')
        self.__painting_service.dump_to_json(filename)
        print(f'\nPictorii au fost exportati in {filename}.json!\n')

    def __handle_expensive_paintings(self):
        """
        Permite utilizatorului sa vada tabloul cel mai scump pentru fiecare stil.
        :return: None
        """
        lst_paintings = self.__painting_service.expensive_paintings()
        if lst_paintings == {}:
            print('\nNu au fost gasiti pictori inregistrati.')
        else:
            for each_painting in lst_paintings:
                print(f'Stilul {each_painting}, are tabloul cu pret maxim : {lst_paintings[each_painting]}')

    def run_console(self):
        """
        Ruleaza interfata cu utilizatorul pentru functionalitati asupra obiectelor tablou si obiectelor pictor
        :return: None
        """
        while True:
            self.__print_menu()

            user_option = input('Selectati optiunea dorita: ').strip()

            if user_option == '1':
                self.__handle_add_artist()
            elif user_option == 'a':
                self.__handle_read_artists()
            elif user_option == '2':
                self.__handle_add_painting()
            elif user_option == 'b':
                self.__handle_read_paintings()
            elif user_option == '3':
                self.__handle_expensive_paintings()
            elif user_option == '4':
                self.__handle_sort_artists_by_paintings()
            elif user_option == '5':
                self.__export_json()
            elif user_option == 'x':
                return
            else:
                print('\nOptiune invalida!')
