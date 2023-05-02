import jsonpickle
from Domain.entity import Entity


class FileRepository:
    """
    Reprezinta un repository cu fisiere pentru obiectele unei alte clase
    """

    def __init__(self, filename):
        self.__filename = filename
        self.__storage = {}
        try:
            self.__load_file()
        except:
            self.__write_file()

    def __write_file(self):
        """
        Realizeaza memorarea pe disk a repository-ului, in fisierul TXT cu numele din atributul filename
        :return: None
        """
        with open(self.__filename, 'w') as f:
            f.write(jsonpickle.encode(self.__storage))

    def __load_file(self):
        """
        Preia repository-ul memorat pe disk in fisierul TXT cu numele din atributul filename
        :return: None
        """
        with open(self.__filename, 'r') as g:
            try:
                self.__storage = jsonpickle.decode(g.read())
            except:
                self.__storage = {}

    def get_by_id(self, given_id):
        """
        Cauta un obiect in repository-ul din fisierul asignat, dupa ID
        :param given_id: id-ul dat, str
        :return: obiectul cu ID-ul dat / NONE daca nu este gasit
        """

        self.__load_file()
        if given_id in self.__storage.keys():
            return self.__storage[given_id]
        else:
            return None

    def create(self, other: Entity):
        """
        Creeaza o noua intrare in repository cu un obiect nou
        :param other: obiectul nou, Entity
        :raises: KeyError daca exista deja un obiect cu ID-ul celui dat
        :return: None
        """

        if self.get_by_id(other.id) is not None:
            raise KeyError(f'Exista deja o entitate de acest tip cu id-ul {other.id}')
        self.__storage[other.id] = other
        self.__write_file()

    def read(self):
        """
        Returneaza repository-ul din fisierul de pe disk sub forma de lista sortata ASC dupa ID
        :return: repository-ul, list
        """

        self.__load_file()
        db = list(self.__storage.values())
        db.sort(key=lambda x: x.id)
        return db

    def update(self, other: Entity):
        """
        Modifica o intrare din repository, suprascriind obiectul cu altul cu acelasi ID
        :param other: obiectul actualizat, Entity
        :raises: KeyError daca nu exista un obiect cu ID-ul furnizat
        :return: None
        """

        if self.get_by_id(other.id) is None:
            raise KeyError(f'Nu exista o entitate de acest tip cu id-ul {other.id}')
        self.__storage[other.id] = other
        self.__write_file()

    def delete(self, given_id):
        """
        Sterge o intrare din repository, pe baza de ID
        :param given_id: ID-ul dat, str
        :raises: KeyError daca nu exista un obiect cu ID-ul furnizat
        :return: None
        """

        if self.get_by_id(given_id) is None:
            raise KeyError(f'Nu exista o entitate de acest tip cu ID-ul {given_id}')
        del self.__storage[given_id]
        self.__write_file()
