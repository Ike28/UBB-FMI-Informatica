from datetime import date

import jsonpickle

from Domain.card_client import CardClient
from Repository.file_repository import FileRepository


class CardClientValidate:
    """

    """

    def __init__(self, filename):
        self.__filename = filename
        try:
            with open(filename, 'r') as f:
                self.__ssn_storage = jsonpickle.decode(f.read())
        except:
            with open(filename, 'w') as g:
                g.write(jsonpickle.encode({}))

    def validate(self, other: CardClient, check_cnp=True, check_id=True):
        with open(self.__filename, 'r') as f:
            self.__ssn_storage = jsonpickle.decode(f.read())
        errors = ''

        try:
            test_ssn = int(other.ssn)
        except KeyError as ke:
            errors += '\n' + str(ke)

        if other.id is None:
            raise ValueError('\nID-ul introdus nu este un numar.')

        if other.id < 0:
            errors += '\nNu sunt acceptate ID-uri mai mici decat 1.'

        if check_id is True and str(other.id) in self.__ssn_storage:
            errors += f'\nExista deja un card cu ID-ul {other.id}.'

        if len(other.ssn) < 13:
            errors += '\nCNP-ul are o lungime invalida.'

        if check_cnp is True and other.ssn in self.__ssn_storage.values():
            errors += f'\nExista deja un card cu CNP-ul {other.ssn}.'

        if type(other.birth_day) is not date:
            errors += '\nData nasterii are un format invalid.'

        if type(other.registration_date) is not date:
            errors += '\nData inregistrarii are un format invalid.'

        if other.points < 0:
            errors += '\nNumarul de puncte trebuie sa fie pozitiv.'

        if len(errors):
            raise ValueError(errors)

        self.__ssn_storage[other.id] = other.ssn

        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__ssn_storage))

    def delete_id(self, card_id):
        with open(self.__filename, 'r') as f:
            self.__ssn_storage = jsonpickle.decode(f.read())
        del self.__ssn_storage[str(card_id)]
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__ssn_storage))
