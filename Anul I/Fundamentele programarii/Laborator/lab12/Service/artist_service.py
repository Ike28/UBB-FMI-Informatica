from Repository.file_repository import FileRepository
from Domain.artist import Artist
from Domain.artist_validator import ArtistValidator


class ArtistService:
    """
    Defineste serviciul de functionalitati pentru obiecte de tip pictor (Artist)
    """
    def __init__(self, artist_repository: FileRepository, artist_validator: ArtistValidator):
        """
        Creeaza un serviciu de functionalitati pentru obiecte ale clasei Artist
        :param artist_repository: repository-ul obiectelor, obiect al clasei FileRepository
        :param artist_validator: validator pentru obiecte Artist, obiect al clasei ArtistValidator
        """
        self.__repository = artist_repository
        self.__validator = artist_validator

    def read(self):
        """
        Citeste repository-ul si returneaza o lista continand obiectele Artist inregistrate
        :return: lista obiectelor, list
        """
        return self.__repository.read()

    def read_by_id(self, given_id):
        """
        Cauta in repository obiectul Artist cu un ID dat, si il returneaza
        :param given_id: ID-ul dupa care se cauta, string reprezentand un numar intreg
        :return: Artist daca ID-ul exista in repository / None altfel
        """
        return self.__repository.get_by_id(given_id)

    def create(self, given_id, given_name, given_style):
        """
        Creeaza o noua inregistrare de obiect pictor in repository
        :param given_id: ID-ul pictorului, string reprezentand numar intreg
        :param given_name: numele pictorului, string nenul
        :param given_style: stilul pictorului, string din multimea {modern, clasic, abstract}
        :return: None
        :raises: ValueError daca datele nu sunt valide
        """
        new_artist = Artist(given_id, given_name, given_style)
        self.__validator.validate(new_artist)
        self.__repository.create(new_artist)
