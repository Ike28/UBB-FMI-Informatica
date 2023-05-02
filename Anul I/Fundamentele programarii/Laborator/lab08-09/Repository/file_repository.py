import jsonpickle
from Domain.entity import Entity
from Domain.mysorts import MySorts


class FileRepository:
    """
    Descrie un repository generic pastrat in fisier
    """

    def __init__(self, filename):
        """
        Creeaza un obiect de tipul repository cu fisiere
        :param filename: numele fisierului dat
        """
        self.__storage = {}
        self.__filename = filename

    @property
    def storage(self):
        return self.__storage

    def write_file(self):
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__storage))

    def load_file(self):
        with open(self.__filename, 'r') as f:
            try:
                self.__storage = jsonpickle.decode(f.read())
            except:
                self.__storage = {}

    def get_all(self):
        self.load_file()
        return MySorts.my_sorted(list(self.__storage.values()), key=lambda x: x.id)

    def get_by_id(self, given_id):
        self.load_file()
        if str(given_id) in self.__storage:
            return self.__storage[str(given_id)]
        return None

    def create(self, other: Entity):
        if self.get_by_id(other.id) is not None:
            raise KeyError(f'Exista deja o entitate cu id-ul {other.id}!')
        self.__storage[other.id] = other
        self.write_file()

    def update(self, other: Entity):
        if self.get_by_id(other.id) is None:
            raise KeyError(f'Nu exista nicio enitate cu id-ul {other.id}')
        self.__storage[other.id] = other
        self.write_file()

    def delete(self, given_id):
        if self.get_by_id(str(given_id)) is None:
            raise KeyError(f'Nu exista nicio entitate cu id-ul {given_id}')
        del self.__storage[str(given_id)]
        self.write_file()
