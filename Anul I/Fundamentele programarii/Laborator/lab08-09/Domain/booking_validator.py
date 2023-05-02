import jsonpickle

from Domain.booking import Booking
from Repository.file_repository import FileRepository


class BookingValidate:
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

    def validate(self, other: Booking, check_id=True):
        with open(self.__filename, 'r') as f:
            self.__id_storage = jsonpickle.decode(f.read())
        errors = ''

        if other.id is None:
            raise ValueError('\nID-ul introdus nu este un numar.')

        if other.id < 1:
            errors += '\nNu sunt acceptate ID-uri mai mici decat 1.'

        if check_id is True and other.id in self.__id_storage:
            errors += f'\nExista deja o rezervare cu ID-ul {other.id}.'

        if other.film.on_screen is False:
            errors += '\nFilmul pentru care se doreste rezervarea nu este in program.'

        if len(errors):
            raise ValueError(errors)

        self.__id_storage.append(other.id)

        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__id_storage))

    def delete_id(self, del_id):
        with open(self.__filename, 'r') as f:
            self.__id_storage = jsonpickle.decode(f.read())
        new_storage = []
        for each in self.__id_storage:
            if each != del_id:
                new_storage.append(each)
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(new_storage))
