from Domain.entity_validator import EntityValidator
from Repository.file_repository import FileRepository
from Domain.city import City


class CityValidator(EntityValidator):
    def __init__(self):
        super(CityValidator, self).__init__()

    def validate(self, other: City, city_repository: FileRepository):
        super(CityValidator, self).validate(other, city_repository)

        errors = ''

        if other.name == '':
            errors += '\nNumele orasului nu poate fi gol.'

        other.population = int(other.population)

        if other.population < 0:
            errors += '\nPopulatia orasului nu poate fi mai mica decat 0.'

        if len(errors):
            raise KeyError(errors)

        return other
