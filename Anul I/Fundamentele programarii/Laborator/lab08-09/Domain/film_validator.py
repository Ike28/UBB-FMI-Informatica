import jsonpickle
from Domain.film import Film
from Repository.file_repository import FileRepository


class FilmValidate:
    """

    """

    def __init__(self, filename):
        self.__filename = filename
        try:
            with open(filename, 'r') as f:
                self.__id_storage = jsonpickle.decode(f.read())
        except:
            with open(filename, 'w') as g:
                g.write(jsonpickle.encode([]))

    def validate(self, given_film: Film, check_id=True):
        with open(self.__filename, 'r') as f:
            self.__id_storage = jsonpickle.decode(f.read())

        errors = ''

        if given_film.id is None:
            raise ValueError('\nID-ul introdus nu este un numar.')

        if given_film.id < 1:
            errors += '\nNu sunt acceptate ID-uri mai mici decat 1.'

        if check_id is True and given_film.id in self.__id_storage:
            errors += f'\nExista deja un film cu ID-ul {given_film.id}.'

        if given_film.title == '':
            errors += '\nFilmul trebuie sa aiba un titlu.'

        if given_film.ticket_price <= 0:
            errors += '\nPretul filmului trebuie sa fie strict pozitiv.'

        if given_film.on_screen not in [True, False]:
            errors += '\nNu se poate determina daca filmul este sau nu in program.'

        if given_film.year < 1850:
            errors += '\nAnul filmului este inadmisibil.'

        if len(errors):
            raise ValueError(errors)

        self.__id_storage.append(given_film.id)
        with open(self.__filename, 'w') as g:
            g.write(jsonpickle.encode(self.__id_storage))

    def delete_id(self, del_id):
        with open(self.__filename, 'r') as f:
            self.__id_storage = jsonpickle.decode(f.read())
        new_storage = []
        for each in self.__id_storage:
            if each != del_id:
                new_storage.append(each)
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(new_storage))
