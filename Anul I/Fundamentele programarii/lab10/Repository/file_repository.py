import jsonpickle
from Domain.entity import Entity


class FileRepository:
    def __init__(self, filename):
        self.__filename = filename
        self.__storage = {}
        try:
            self.__load_file()
        except:
            self.__write_file()

    def __write_file(self):
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__storage))

    def __load_file(self):
        with open(self.__filename, 'r') as g:
            try:
                self.__storage = jsonpickle.decode(g.read())
            except:
                self.__storage = {}

    def get_by_id(self, given_id):
        self.__load_file()
        if given_id in self.__storage.keys():
            return self.__storage[given_id]
        else:
            return None

    def create(self, other: Entity):
        if self.get_by_id(other.id) is not None:
            raise KeyError(f'Exista deja o entitate de acest tip cu id-ul {other.id}')
        self.__storage[other.id] = other
        self.__write_file()

    def read(self):
        self.__load_file()
        database = list(self.__storage.values())
        database.sort(key=lambda x: x.id)
        return database

    def update(self, other: Entity):
        if self.get_by_id(other.id) is None:
            raise KeyError(f'Nu exista o entitate de acest tip cu id-ul {other.id}')
        self.__storage[other.id] = other
        self.__write_file()

    def delete(self, given_id):
        if self.get_by_id(given_id) is None:
            raise KeyError(f'Nu exista o entitate de acest tip cu ID-ul {given_id}')
        del self.__storage[given_id]
        self.__write_file()
