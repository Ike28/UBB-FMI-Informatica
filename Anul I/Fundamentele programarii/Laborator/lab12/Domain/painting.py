from Domain.entity import Entity


class Painting(Entity):
    """
    Defineste conceptul de tablou pictat ca obiect
    """
    def __init__(self, given_id, given_artist_id, given_title, given_price, given_year):
        """
        Defineste un obiect de tipul tablou
        :param given_id: ID-ul tabloului, str ce reprezinta numar
        :param given_artist_id: ID-ul artistului care l-a pictat
        :param given_title: titlul tabloului, str cu len>0
        :param given_price: pretul tabloului, int>0
        :param given_year: anul realizarii tabloului, int>0
        """
        super(Painting, self).__init__(given_id)
        self.__artist_id = given_artist_id
        self.__title = given_title
        self.__price = given_price
        self.__year = given_year

    @property
    def artist_id(self):
        return self.__artist_id

    @artist_id.setter
    def artist_id(self, value: str):
        self.__artist_id = value

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, value: str):
        self.__title = value

    @property
    def price(self):
        return self.__price

    @price.setter
    def price(self, value: int):
        self.__price = value

    @property
    def year(self):
        return self.__year

    @year.setter
    def year(self, value: int):
        self.__year = value

    def __str__(self):
        return f'ID: {self.id} | Tabloul "{self.title}" \n--->creat de artistul {self.artist_id} \n--->in anul {self.year}\n--->licitat la pretul de {self.price} lei.'
