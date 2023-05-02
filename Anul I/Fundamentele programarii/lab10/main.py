from Domain.city_validator import CityValidator
from Domain.street_validator import StreetValidator
from Repository.file_repository import FileRepository
from Service.city_service import CityService
from Service.street_service import StreetService
from UserInterface.console import Console


def run_database():
    city_filename = Console.get_file_name('Introduceti fisierul in care se vor scrie orasele: ')
    city_repository = FileRepository(city_filename)
    city_validator = CityValidator()

    street_filename = Console.get_file_name('Introduceti fisierul in care se vor scrie strazile: ')
    street_repository = FileRepository(street_filename)
    street_validator = StreetValidator()

    city_service = CityService(city_repository, city_validator)
    street_service = StreetService(street_repository, street_validator, city_repository)

    user_interface = Console(city_service, street_service)
    user_interface.run_interface()


run_database()
