import jsonpickle

from Domain.painting import Painting
from Domain.painting_validator import PaintingValidator
from Repository.file_repository import FileRepository
from ViewModels.painting_viewmodel import PaintingViewModel


class PaintingService:
    """
    Defineste serviciul de functionalitati pentru obiecte de tip tablou (Painting)
    """
    def __init__(self, painting_repository: FileRepository, painting_validator: PaintingValidator, artist_repository: FileRepository):
        """
        Creeaza un serviciu de functionalitati pentru obiecte ale clasei Painting
        :param painting_repository: repository-ul obiectelor, obiect al clasei FileRepository
        :param painting_validator: validator pentru obiecte Painting, obiect al clasei PaintingValidator
        :param artist_repository: repository-ul obiectelor pictor cu care se coreleaza tablourile, obiect FileRepository
        """
        self.__repository = painting_repository
        self.__validator = painting_validator
        self.__artist_repository = artist_repository

    def read(self):
        """
        Citeste repository-ul si returneaza o lista continand obiectele Painting inregistrate
        :return: lista obiectelor, list
        """
        return self.__repository.read()

    def read_by_id(self, given_id):
        """
        Cauta in repository obiectul Painting cu un ID dat, si il returneaza
        :param given_id: ID-ul dupa care se cauta, string reprezentand un numar intreg
        :return: Painting daca ID-ul exista in repository / None altfel
        """
        return self.__repository.get_by_id(given_id)

    def create(self, given_id, given_artist_id, given_title, given_price, given_year):
        """
        Creeaza o noua inregistrare de obiect tablou in repository
        :param given_id: ID-ul tabloului, string reprezentand numar intreg
        :param given_artist_id: ID-ul pictorului ce a realizat tabloul, string reprezentand numar intreg, trebuie sa existe
        in repository
        :param given_title: titlul tabloului, string nenul
        :param given_price: pretul tabloului, string reprezentand numar intreg strict pozitiv
        :param given_year: anul realizarii tabloului, string reprezentand numar intreg strict pozitiv
        :return: None
        :raises: ValueError daca datele nu sunt valide
        """

        author = self.__artist_repository.get_by_id(given_artist_id)
        if author is None:
            raise ValueError(f'\nArtistul cu id-ul {given_artist_id} nu a fost gasit.')
        new_painting = Painting(given_id, given_artist_id, given_title, given_price, given_year)
        valid_painting = self.__validator.validate(new_painting)
        author.add_painting(valid_painting)
        self.__artist_repository.update(author)
        self.__repository.create(valid_painting)

    def to_str(self, other: Painting):
        """
        Efectueaza conversia unui obiect tablou la string afisabil pe ecran
        :param other: tabloul, obiect Painting
        :return: rezultatul, string (vezi formatarea in ViewModels)
        """
        return str(PaintingViewModel(other, self.__artist_repository.get_by_id(other.artist_id)))

    def get_artists_by_number_of_paintings(self, inaugural_year):
        """
        Sorteaza pictorii din repository dupa numarul de tablouri inregistrate pictate de fiecare, descrescator
        pentru tablourile realizate de la un an dat incolo
        :param inaugural_year: anul dupa care se compara, int>0
        :return: dict de forma {id_artist:numar_tablouri}
        """
        artist_list = self.__artist_repository.read()
        artist_ids, count_of_paintings = [], []
        for each in artist_list:
            artist_ids.append(each.id)
            count_of_paintings.append(0)
        painting_list = [painting for painting in self.__repository.read() if painting.year >= inaugural_year]
        for each in painting_list:
            if each.artist_id in artist_ids:
                count_of_paintings[artist_ids.index(each.artist_id)] += 1
        sorted_artists = {artist_id: painting_number for artist_id, painting_number in sorted(
            list(zip(artist_ids, count_of_paintings)), key=lambda x: x[1], reverse=True)}
        return sorted_artists

    def expensive_paintings(self):
        """
        Returneaza cele mai scumpe tablouri pentru fiecare stil
        :return:
        """
        painting_list = self.__repository.read()
        result = {}
        for each_painting in painting_list:
            artist = self.__artist_repository.get_by_id(each_painting.artist_id)
            style = artist.style
            if style not in result:
                result[style] = each_painting
            else:
                if each_painting.price > result[style].price:
                    result[style] = each_painting
        return result

    def dump_to_json(self, filename: str):
        """
        Exporta pictorii intr-un fisier cu extensie .json
        :param filename: Numele fisierului dat
        :return: None
        """
        filename += '.json'
        result = {}
        artists = self.__artist_repository.read()
        for each_artist in artists:
            result[each_artist.id] = each_artist
        with open(filename, 'w') as f:
            f.write(jsonpickle.encode(result))
