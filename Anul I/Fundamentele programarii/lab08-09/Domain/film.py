from Domain.entity import Entity


class Film(Entity):
    """
    Descrie un film
    """

    def __init__(self, given_title, launch_year, given_price, on_screen=False, given_id=None):
        """
        Creeaza un obiect de tip Film
        :param given_title: titlul filmului, string
        :param launch_year: anul aparitiei, int > 1850
        :param given_price: pretul unui bilet, float > 0
        :param on_screen: este sau nu in program, bool
        :param given_id: id-ul filmului
        """
        super().__init__(given_id)
        self.__title = given_title
        self.__year = launch_year
        self.__ticket_price = given_price
        self.__on_screen = on_screen
        
    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, value):
        self.__title = value

    @property
    def year(self):
        return self.__year

    @year.setter
    def year(self, value):
        self.__year = value

    @property
    def ticket_price(self):
        return self.__ticket_price

    @ticket_price.setter
    def ticket_price(self, value):
        self.__ticket_price = value

    @property
    def on_screen(self):
        return self.__on_screen

    @on_screen.setter
    def on_screen(self, value):
        self.__on_screen = value

    def __str__(self):
        if not self.on_screen:
            return f'ID: {self.id} - Filmul "{self.title}" aparut in {self.year} cu pretul de {self.ticket_price} lei/bilet, nu este in program.'
        else:
            return f'ID: {self.id} - Filmul "{self.title}" aparut in {self.year} cu pretul de {self.ticket_price} lei/bilet, este in program.'

    def search(self, string_to_search):
        for prop in [self.title, str(self.year)]:
            if string_to_search in prop:
                return True
        return False
