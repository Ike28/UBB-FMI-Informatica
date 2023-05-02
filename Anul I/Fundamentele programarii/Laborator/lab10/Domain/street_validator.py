from Domain.entity_validator import EntityValidator
from Domain.street import Street
from Repository.file_repository import FileRepository


class StreetValidator(EntityValidator):
    def __init__(self):
        super(StreetValidator, self).__init__()

    def validate(self, other: Street, street_repsitory: FileRepository, city_repository: FileRepository):
        super(StreetValidator, self).validate(other, street_repsitory)

        errors = ''

        cities_id = []
        existing_cities = city_repository.read()
        for each_city in existing_cities:
            cities_id.append(each_city.id)
        if other.city_id not in cities_id:
            errors += f'\nOrasul cu ID-ul {other.city_id} nu exista.'

        if other.name == '':
            errors += '\nNumele strazii nu poate fi gol.'

        other.length = int(other.length)

        if other.length < 1:
            errors += '\nLungimea trebuie sa fie cel putin 1km.'

        if len(errors):
            raise KeyError(errors)

        return other
