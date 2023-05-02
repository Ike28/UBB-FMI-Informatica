from datetime import date
from Domain.mysorts import MySorts
from Domain.add_operation import AddOperation
from Domain.card_client import CardClient
from Domain.card_client_validator import CardClientValidate
from Domain.delete_operation import DeleteOperation
from Domain.update_operation import UpdateOperation
from Repository.file_repository import FileRepository
from datetime import time, datetime

from Service.undo_redo_service import UndoRedoService


class CardClientService:
    """
    Descrie un serviciu ce realizeaza operatiuni asupra unei baze de date de carduri de client
    """

    def __init__(self, card_repository: FileRepository, card_validator: CardClientValidate, undo_redo_service: UndoRedoService):
        """
        Creeaza un obiect de tipul serviciu pentru obiecte de tip card client
        :param card_repository: repository pentru obiectele card client, obiect CardClientRepository
        :param card_validator: validator pentru obiectele card client, obiect CardClientValidate
        """
        self.__card_repository = card_repository
        self.__card_validator = card_validator
        self.__undo_redo = undo_redo_service

    def create(self, given_id, given_surname, given_name, given_ssn, given_date, given_points):
        """
        Creeaza un card client in repository
        :param given_id: id-ul cardului, int
        :param given_surname: numele de familie al clientului, string
        :param given_name: prenumele clientului, string
        :param given_ssn: CNP-ul clientului, string de lungime 13
        :param given_date: data inregistrarii clientului, date
        :param given_points: punctele acumulate pe card, int
        :return: None
        """
        new_card = CardClient(given_surname, given_name, given_ssn, given_date, given_points, given_id)
        self.__card_validator.validate(new_card)
        self.__card_repository.create(new_card)
        self.__undo_redo.add_undo(AddOperation(self.__card_repository, new_card))

    def delete(self, given_id):
        """
        Sterge un card din repository pe baza de id
        :param given_id: id-ul cardului, int
        :return: None
        """
        deleted_card = self.__card_repository.get_by_id(given_id)
        self.__card_repository.delete(given_id)
        self.__card_validator.delete_id(given_id)
        self.__undo_redo.add_undo(DeleteOperation(self.__card_repository, deleted_card))

    def update(self, given_id, given_surname, given_name, given_ssn, given_date, given_points):
        """
        Modifica un card din repository pe baza de id
        :param given_id: id-ul cardului, int
        :param given_surname: numele de familie, string
        :param given_name: prenumele, string
        :param given_ssn: CNP-ul clientului, string de lungime 13
        :param given_date: data inregistrarii clientului, date
        :param given_points: punctele acumulate pe card, int
        :raises: KeyError daca id-ul cardului nu exista in repository sau datele sunt de alt tip
        :return: None
        """
        searched_card = self.__card_repository.get_by_id(given_id)
        if searched_card is None:
            raise KeyError(f'Cardul cu ID-ul {given_id} nu exista')

        if given_surname == '':
            given_surname = searched_card.surname
        if given_name == '':
            given_name = searched_card.name
        if given_ssn == '':
            given_ssn = searched_card.ssn
            check_cnp = False
        else:
            check_cnp = True
        if given_date == '':
            given_date = searched_card.registration_date
        elif type(given_date) != date:
            read_date = given_date.split('.')
            given_date = date(int(read_date[2]), int(read_date[1]), int(read_date[0]))
        if given_points == '':
            given_points = searched_card.points
        else:
            given_points = float(given_points)

        new_card = CardClient(given_surname, given_name, given_ssn, given_date, given_points, given_id)
        self.__card_validator.validate(new_card, check_cnp, check_id=False)

        self.__card_repository.update(new_card)
        self.__undo_redo.add_undo(UpdateOperation(self.__card_repository, searched_card, new_card))

    def read(self):
        """
        Returneaza lista cardurilor de client existente in repository
        :return: list
        """
        return self.__card_repository.get_all()

    def read_by_id(self, given_id):
        """
        Returneaza un card client existent in repository pe baza de id
        :param given_id: id-ul de cautat, int
        :return: CardClient daca id-ul exista in repository / None altfel
        """
        return self.__card_repository.get_by_id(given_id)

    def full_search(self, string_to_search):
        """

        :param string_to_search:
        :return:
        """

        search_results = []
        card_list = self.__card_repository.get_all()
        for each_card in card_list:
            if each_card.search(string_to_search):
                search_results.append(each_card)
        return search_results

    def sort_by_points_desc(self):
        """

        :return:
        """

        card_list = self.__card_repository.get_all()
        # card_list.sort(key=lambda x: x.points, reverse=True)
        return MySorts.my_sorted(card_list, key=lambda x: x.points, reverse=True)

    def apply_birthday_bonus(self, birth_day: date, points_increase: float):
        """

        :return:
        """

        errors = ''
        if datetime.combine(birth_day, time(0, 0)) > datetime.today():
            errors += '\nNu se pot acorda bonusuri clientilor ce nu s-au nascut.'
        if points_increase < 0:
            errors += '\nBonusul aniversar nu poate sa taie din punctele clientilor.'
        if points_increase == 0:
            errors += '\nBonusul aniversar nu poate fi zero.'
        if len(errors):
            raise ValueError(errors)
        

        birthdays = 0
        cards_list = self.__card_repository.get_all()
        for card in cards_list:
            if card.birth_day == birth_day:
                birthdays += 1
                card.points = card.points + points_increase
                self.update(card.id, card.surname, card.name, '', card.registration_date, card.points)
        return birthdays
