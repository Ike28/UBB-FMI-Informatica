from Domain.booking_validator import BookingValidate
from Domain.card_client_validator import CardClientValidate
from Domain.film_validator import FilmValidate
from Repository.file_repository import FileRepository
from Service.booking_service import BookingService
from Service.cardclient_service import CardClientService
from Service.film_service import FilmService
from Service.undo_redo_service import UndoRedoService
from Tests.run_all_tests import run_all_tests
from UserInterface.console import Console


def run_database():
    film_repository = FileRepository('films.txt')
    film_validator = FilmValidate('film_ids.txt')

    card_repository = FileRepository('cards.txt')
    card_validator = CardClientValidate('card_ids.txt')

    booking_repository = FileRepository('bookings.txt')
    booking_validator = BookingValidate('booking_ids.txt')

    undo_redo_service = UndoRedoService()
    film_service = FilmService(film_repository, film_validator, undo_redo_service)
    card_service = CardClientService(card_repository, card_validator, undo_redo_service)
    booking_service = BookingService(booking_repository, booking_validator, film_repository, card_repository, undo_redo_service)

    user_interface = Console(film_service, card_service, booking_service, undo_redo_service)
    user_interface.run_console()


run_all_tests()
run_database()
