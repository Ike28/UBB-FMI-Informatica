from Tests.test_entity import test_entity_constructor_validator
from Tests.test_file_repository import test_file_repository
from Tests.test_film import test_film_constructor_validator
from Tests.test_card import test_card_constructor_validator
from Tests.test_booking import test_booking_constructor_validator
from Tests.test_booking_service import test_booking_service
from Tests.test_cardclient_service import test_card_service
from Tests.test_film_service import test_film_service
from Tests.test_my_sorts import test_my_sorts


def run_all_tests():
    test_entity_constructor_validator()
    test_film_constructor_validator()
    test_card_constructor_validator()
    test_booking_constructor_validator()
    test_file_repository()
    test_card_service()
    test_film_service()
    test_booking_service()
    test_my_sorts()
