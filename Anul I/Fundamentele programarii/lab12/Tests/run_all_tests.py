from Tests.test_artist import test_artist_constructor_validator
from Tests.test_artist_service import test_artist_service
from Tests.test_file_repository import *
from Tests.test_painting import test_painting_constructor_validator
from Tests.test_painting_service import test_painting_service


def run_all_tests():
    test_file_repository()
    test_artist_constructor_validator()
    test_artist_service()
    test_painting_constructor_validator()
    test_painting_service()
