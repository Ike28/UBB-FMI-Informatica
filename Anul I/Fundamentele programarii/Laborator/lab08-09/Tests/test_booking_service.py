from datetime import date, time

import jsonpickle

from Domain.film import Film
from Domain.card_client import CardClient
from Domain.booking import Booking
from Domain.booking_validator import BookingValidate
from Repository.file_repository import FileRepository
from Service.booking_service import BookingService
from Service.undo_redo_service import UndoRedoService


def test_booking_service():
    with open('test_films.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_cards.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_bookings.txt', 'w') as f:
        f.write(jsonpickle.encode({}))
    with open('test_booking_ids.txt', 'w') as f:
        f.write(jsonpickle.encode([]))

    film_repository = FileRepository('test_films.txt')
    card_repository = FileRepository('test_cards.txt')
    booking_repository = FileRepository('test_bookings.txt')
    booking_validator = BookingValidate('test_booking_ids.txt')
    undo_redo = UndoRedoService()
    booking_service = BookingService(booking_repository, booking_validator, film_repository, card_repository, undo_redo)

    film_repository.create(Film('aaa', 1980, 20, True, 1))
    card_repository.create(CardClient('aaa', 'bbb', '6101010400400', date(2020, 1, 1), 200, 2))
    booking_service.create(4, 1, 2, date(2021, 10, 10), time(10, 10))
    booking_service.update(4, '', '', '', time(10, 11))
    booking_service.delete(4, print_result=False)
    assert booking_service.read() == []
    booking_service.create(4, 1, 2, date(2021, 10, 10), time(10, 10))
    assert booking_service.check_bookings_for_card(2) is True
    booking_service.delete_in_interval(date(2000, 1, 1), date(3000, 1, 1), print_result=False)
    booking_service.create(4, 1, 2, date(2021, 10, 10), time(10, 10))
    assert len(booking_service.get_bookings_by_time(time(10, 10), time(23, 23))) == 1
    assert booking_service.count_bookings() == {1: 1}
    assert booking_service.check_bookings_for_film(1) is True
    assert booking_service.check_bookings_for_film(2) is False
