from Domain.entity import Entity
from Repository.file_repository import FileRepository


class EntityValidator:
    def __init__(self):
        self.__id_storage = []

    def validate(self, other: Entity, entity_repository: FileRepository):
        existing_entities = entity_repository.read()
        for each_entity in existing_entities:
            self.__id_storage.append(each_entity.id)

        errors = ''

        try:
            int(other.id)
        except:
            errors += '\nID-ul introdus nu este un numar.'

        if other.id in self.__id_storage:
            errors += f'\nExista deja o entitate de acest tip cu ID-ul {other.id}.'

        if len(errors):
            raise KeyError(errors)
