from Domain.entity_validator import EntityValidator
from Repository.file_repository import FileRepository


class EntityService:
    def __init__(self, ent_repository: FileRepository, ent_validator: EntityValidator):
        self.__repository = ent_repository
        self.__validator = ent_validator

    @property
    def repository(self):
        return self.__repository

    def validator(self):
        return self.__validator

    def read(self):
        return self.__repository.read()

    def read_by_id(self, given_id):
        return self.__repository.get_by_id(given_id)
