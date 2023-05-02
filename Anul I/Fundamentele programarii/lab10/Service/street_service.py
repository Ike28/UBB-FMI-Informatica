from Domain.street import Street
from Domain.street_validator import StreetValidator
from Repository.file_repository import FileRepository
from Service.entity_service import EntityService


class StreetService(EntityService):
    def __init__(self, street_repository: FileRepository, street_validator: StreetValidator, city_repository: FileRepository):
        super(StreetService, self).__init__(street_repository, street_validator)
        self.__city_repository = city_repository

    def create(self, given_id, given_city_id, given_name, given_length):
        new_street = Street(given_id, given_city_id, given_name, given_length)
        checked_street = self.validator().validate(new_street, self.repository, self.__city_repository)
        self.__city_repository.get_by_id(checked_street.id).add_street(checked_street.name)
        self.repository.create(checked_street)
