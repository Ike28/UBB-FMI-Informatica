from Domain.entity import Entity
from Domain.painting import Painting


class Artist(Entity):
    """
    Defineste conceptul de pictor ca obiect
    """
    def __init__(self, given_id, given_name, given_style):
        """
        Defineste un obiect de tip pictor
        :param given_id: ID-ul pictorului, str ce reprezinta numar
        :param given_name: numele pictorului, str cu len>0
        :param given_style: stilul pictorului, str din multimea {modern, clasic, abstract}
        """
        super(Artist, self).__init__(given_id)
        self.__name = given_name
        self.__style = given_style
        self.__paintings = []

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value: str):
        self.__name = value

    @property
    def style(self):
        return self.__style

    @style.setter
    def style(self, value: str):
        self.__style = value

    @property
    def painting_list(self):
        return self.__paintings

    def add_painting(self, value: Painting):
        self.__paintings.append(value)

    def __str__(self):
        return f'ID: {self.id} | {self.name}, pictor al stilului {self.style}.'
