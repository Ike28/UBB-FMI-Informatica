from Domain.film import Film
from Domain.film_validator import FilmValidate
from Repository.file_repository import FileRepository
from Domain.random import RandomData
from xlsxwriter import Workbook

class FilmService:
    """
    Descrie un serviciu ce realizeaza operatiuni asupra unei baze de date de filme
    """

    def __init__(self, film_repository: FileRepository, film_validator: FilmValidate):
        """
        Creeaza un obiect de tip serviciu pentru obiecte de tip film
        :param film_repository: repository pentru obiectele film, obiect FileRepository
        :param film_validator: validator pentru obiectele film, obiect FilmValidate
        """
        self.__film_repository = film_repository
        self.__film_validator = film_validator

    def create(self, given_id, given_title, launch_year, given_price, is_on_screen):
        """
        Creeaza un film in repository
        :param given_id: id-ul filmului, int
        :param given_title: titlul filmului, string
        :param launch_year: anul aparitiei, int > 1850
        :param given_price: pretul unui bilet, float > 0
        :param is_on_screen: este sau nu in program, bool
        :return: None
        """
        new_film = Film(given_title, launch_year, given_price, is_on_screen, given_id)
        self.__film_validator.validate(new_film)
        self.__film_repository.create(new_film)

    def delete(self, given_id):
        """
        Sterge un film din repository
        :param given_id: id-ul filmului, int
        :return: None
        """
        self.__film_repository.delete(given_id)

    def update(self, given_id, given_title, launch_year, given_price, is_on_screen):
        """
        Modifica un film din repository pe baza de id
        :param given_id: id-ul filmului, int
        :param given_title: titlul, string
        :param launch_year: anul aparitiei, string
        :param given_price: pretul unui bilet, string
        :param is_on_screen: este sau nu in program, bool sau ''
        :raises: KeyError daca id-ul filmului nu exista in repository sau datele nu sunt de tipul corect
        :return: None
        """
        searched_film = self.__film_repository.get_by_id(given_id)
        if searched_film is None:
            raise KeyError(f'Filmul cu ID-ul {given_id} nu exista')

        if given_title == '':
            given_title = searched_film.title
        if given_price == '':
            given_price = searched_film.ticket_price
        else:
            given_price = float(given_price)
        if launch_year == '':
            launch_year = searched_film.year
        else:
            launch_year = int(launch_year)
        if is_on_screen == '':
            is_on_screen = searched_film.on_screen

        new_film = Film(given_title, launch_year, given_price, is_on_screen, given_id)
        self.__film_validator.validate(new_film)

        self.__film_repository.update(new_film)

    def read(self):
        """
        Returneaza lista filmelor din repository
        :return: list
        """
        return self.__film_repository.get_all()

    def read_by_id(self, given_id):
        """
        Returneaza un film existent in repository pe baza de id
        :param given_id: id-ul de cautat, int
        :return: Film daca id-ul exista in repository / None altfel
        """
        return self.__film_repository.get_by_id(given_id)

    def generate_films(self, number_of_films):
        """
        Genereaza un numar de filme cu date aleatorii valide
        :param number_of_films: numarul de filme de generat, int
        :return: None
        """

        generated_list = []
        for i in range(number_of_films):
            rand_id = RandomData.random_int()
            rand_title = RandomData.random_string()
            rand_year = RandomData.random_int(1888, 2025)
            rand_price = RandomData.random_int(1, 200)
            rand_on_screen = RandomData.random_bool()
            generated_film = Film(rand_title, rand_year, rand_price, rand_on_screen, rand_id)
            self.__film_validator.validate(generated_film)
            self.__film_repository.create(generated_film)
            generated_list.append(generated_film)
        return generated_list

    def full_search(self, string_to_search):
        """

        :param string_to_search:
        :return:
        """

        search_results = []
        film_list = self.__film_repository.get_all()
        for each_film in film_list:
            if each_film.search(string_to_search):
                search_results.append(each_film)
        return search_results

    def write_films_to_excel(self):

        new_workbook = Workbook('films.xlsx')
        new_worksheet = new_workbook.add_worksheet()
        new_worksheet.write(0, 0, 'ID Film')
        new_worksheet.write(0, 1, 'Titlu')
        new_worksheet.write(0, 2, 'Anul aparitiei')
        new_worksheet.write(0, 3, 'Pret bilet (lei)')
        new_worksheet.write(0, 4, 'In program')
        films_list = self.__film_repository.get_all()
        row = 1
        for each_film in films_list:
            new_worksheet.write(row, 0, each_film.id)
            new_worksheet.write(row, 1, each_film.title)
            new_worksheet.write(row, 2, each_film.year)
            new_worksheet.write(row, 3, each_film.ticket_price)
            new_worksheet.write(row, 4, each_film.on_screen)
            row += 1
        new_workbook.close()
