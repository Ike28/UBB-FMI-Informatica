from Domain.add_operation import AddOperation
from Domain.booking import Booking
from Domain.booking_validator import BookingValidate
from Domain.card_client import CardClient
from Domain.delete_operation import DeleteOperation
from Domain.update_operation import UpdateOperation
from Repository.file_repository import FileRepository
from datetime import datetime, time, date

from Service.undo_redo_service import UndoRedoService
from Domain.mysorts import MySorts


class BookingService:
    """
    Descrie un serviciu ce realizeaza operatiuni asupra unei baze de date de rezervari
    """

    def __init__(self, booking_repository: FileRepository, booking_validator: BookingValidate, film_repository: FileRepository, card_repository: FileRepository,
                 undo_redo_service: UndoRedoService):
        """
        Creeaza un obiect de tipul serviciu pentru obiecte de tip rezervare film
        :param booking_repository: repository pentru obiectele rezervare, obiect FileRepository
        :param booking_validator: validator pentru obiectele rezervare, obiect BookingValidate
        :param film_repository: repository pentru obiectele film, obiect FileRepository
        :param card_repository: repository pentru obiectele card client, obiect CardClientRepository
        """
        self.__booking_repository = booking_repository
        self.__booking_validator = booking_validator
        self.__film_repository = film_repository
        self.__card_repository = card_repository
        self.__undo_redo = undo_redo_service

    def create(self, given_id, given_film_id, given_card_id, given_date, given_time):
        """
        Creeaza o rezervare in repository
        :param given_id: id-ul rezervarii, int
        :param given_film_id: id-ul filmului, int
        :param given_card_id: id-ul cardului de client, int
        :param given_date: data rezervarii, date
        :param given_time: ora rezervarii, time
        :raises: TypeError pentru id film si/sau card inexistent
        :return: numarul de puncte primite de client in urma rezervarii, float
        """

        errors = ''
        given_film = self.__film_repository.get_by_id(given_film_id)
        if given_film is None:
            errors += f'\nFilmul cu ID-ul {given_film_id} nu exista.'
        given_card = self.__card_repository.get_by_id(given_card_id)
        # if given_card is None:
        #     errors += f'\nCardul cu ID-ul {given_card_id} nu exista.'

        if len(errors):
            raise TypeError(errors)
        new_booking = Booking(given_film, given_date, given_time, given_card, given_id)
        self.__booking_validator.validate(new_booking)
        self.__booking_repository.create(new_booking)

        self.__undo_redo.add_undo(AddOperation(self.__booking_repository, new_booking))

        if given_card is not None:
            return new_booking.points_increase
        return None

    def delete(self, given_id, print_result=True):
        """
        Sterge o rezervare din repository pe baza de id
        :param given_id: id-ul rezervarii, int
        :param print_result: decide daca se va afisa sau nu modificarea punctelor clientului si anularea
        :return: None
        """

        searched_booking = self.__booking_repository.get_by_id(given_id)
        if searched_booking is None:
            raise ValueError(f'\nRezervarea cu ID-ul {given_id} nu exista.')
        if searched_booking.datetime > datetime.now():
            if searched_booking.card is not None:
                card = self.__card_repository.get_by_id(searched_booking.card.id)
                updated_card = CardClient(card.surname, card.name, card.ssn, card.registration_date, card.points - searched_booking.points_increase, card.id)
                self.__card_repository.update(updated_card)

                self.__undo_redo.add_undo(UpdateOperation(self.__card_repository, card, updated_card))

                if print_result is True:
                    return searched_booking.points_increase, updated_card.full_name, updated_card.points
            self.__booking_repository.delete(given_id)
        else:
            self.__booking_repository.delete(given_id)
        self.__booking_validator.delete_id(given_id)
        self.__undo_redo.add_undo(DeleteOperation(self.__booking_repository, searched_booking))

    def update(self, given_id, given_film_id, given_card_id, given_date, given_time):
        """
        Modifica o rezervare din repository pe baza de id
        :param given_id: id-ul rezervarii de modificat, int
        :param given_film_id: id-ul nou al filmului, string
        :param given_card_id: id-ul nou al cardului de client, string
        :param given_date: data rezervarii, date sau ''
        :param given_time: ora rezervarii, time sau ''
        :return: None
        """
        searched_booking = self.__booking_repository.get_by_id(given_id)
        if searched_booking is None:
            raise KeyError(f'Rezervarea cu ID-ul {given_id} nu exista')

        if given_film_id == '':
            given_film = searched_booking.film
        else:
            given_film = self.__film_repository.get_by_id(int(given_film_id))
        if given_card_id == '':
            given_card = searched_booking.card
        else:
            given_card = self.__card_repository.get_by_id(int(given_card_id))
        if given_date == '':
            given_date = searched_booking.date
        if given_time == '':
            given_time = searched_booking.time

        new_booking = Booking(given_film, given_date, given_time, given_card, given_id)
        self.__booking_validator.validate(new_booking, check_id=False)

        self.__booking_repository.update(new_booking)
        self.__undo_redo.add_undo(UpdateOperation(self.__booking_repository, searched_booking, new_booking))

    def read(self):
        """
        Returneaza o lista a rezervarilor din repository
        :return: list
        """
        return self.__booking_repository.get_all()

    def count_bookings(self):
        """
        Returneaza un dictionar de forma "id_film":numar_rezervari, sortat dupa numarul de rezervari
        :return: dict
        """
        film_list = self.__film_repository.get_all()
        film_ids, number_of_bookings = [], []
        for each_film in film_list:
            film_ids.append(each_film.id)
            number_of_bookings.append(0)
        booking_list = self.__booking_repository.get_all()
        for each_booking in booking_list:
            if each_booking.film.id in film_ids:
                number_of_bookings[film_ids.index(each_booking.film.id)] += 1
        sorted_films_by_bookings = {film_id: nr_bookings for film_id, nr_bookings in sorted(zip(film_ids, number_of_bookings), key=lambda element: element[1])}
        return sorted_films_by_bookings

    def get_bookings_by_time(self, start_hour: time, end_hour: time):
        """

        :param start_hour:
        :param end_hour:
        :return:
        """

        valid_bookings = []

        bookings_list = self.__booking_repository.get_all()
        return list(filter(lambda element: start_hour <= element.time <= end_hour, bookings_list))

    def delete_in_interval(self, start_day: date, stop_day: date, print_result=True):
        """

        :param start_day:
        :param stop_day:
        :param print_result: decide daca se va afisa sau nu modificarea punctelor clientului si anularea
        :return:
        """
        bookings_list = self.__booking_repository.get_all()
        deletions = 0
        for each_booking in bookings_list:
            if start_day <= each_booking.date <= stop_day:
                self.delete(each_booking.id, print_result)
                deletions += 1
        return deletions

    def check_bookings_for_film(self, film_id):
        bookings_list = self.__booking_repository.get_all()
        for each_booking in bookings_list:
            if each_booking.film.id == film_id:
                return True
        return False

    def check_bookings_for_card(self, card_id):
        bookings_list = self.__booking_repository.get_all()
        for each_booking in bookings_list:
            if each_booking.card.id == card_id:
                return True
        return False
