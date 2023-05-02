import jsonpickle

from Domain.city_validator import CityValidator
from Repository.file_repository import FileRepository
from Service.entity_service import EntityService
from Domain.city import City


# noinspection PyCallByClass
class CityService(EntityService):
    def __init__(self, city_repository: FileRepository, city_validator: CityValidator):
        super(CityService, self).__init__(city_repository, city_validator)

    def create(self, given_id, given_name, given_population):
        new_city = City(given_id, given_name, given_population)
        checked_city = self.validator().validate(new_city, self.repository)
        self.repository.create(checked_city)

    def dump_cities(self, filename: str):
        with open(filename, 'w') as f:
            f.write(jsonpickle.encode(self.repository.read()))
