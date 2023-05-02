from Domain.entity import Entity
from datetime import date


class CardClient(Entity):
    """
    Descrie cardul unui client
    """

    def __init__(self, given_surname, given_name, given_ssn, given_date, given_points=0, given_id=None):
        """
        Creeaza un obiect de tip Card Client
        :param given_surname: nume de familie client, string
        :param given_name: prenume client, string
        :param given_ssn: CNP-ul clientului, string de dimensiune 13
        :param given_date: data inregistrarii, date
        :param given_points: punctele acumulate pe card, int
        :param given_id: id-ul cardului
        """
        super().__init__(given_id)
        self.__surname = given_surname
        self.__name = given_name
        self.__ssn = given_ssn
        year = int('20' + given_ssn[1] + given_ssn[2])
        if year > date.today().year:
            year = int('19' + given_ssn[1] + given_ssn[2])
        month = int(given_ssn[3] + given_ssn[4])
        day = int(given_ssn[5] + given_ssn[6])
        self.__birth_day = date(year, month, day)
        self.__registration_date = given_date
        self.__points = given_points
    
    @property
    def surname(self):
        return self.__surname
    
    @property
    def name(self):
        return self.__name
    
    @property
    def full_name(self):
        return self.__name + ' ' + self.__surname
    
    @property
    def ssn(self):
        return self.__ssn

    @property
    def birth_day(self):
        return self.__birth_day
    
    @property
    def registration_date(self):
        return self.__registration_date

    @registration_date.setter
    def registration_date(self, value: date):
        self.__registration_date = value

    @property
    def points(self):
        return self.__points

    @points.setter
    def points(self, value):
        self.__points += value

    def __str__(self):
        return f'ID: {self.id} - Cardul clientului NUME: {self.surname} ; PRENUME: {self.name} ; CNP: {self.ssn} ; nascut in {self.birth_day}; inregistrat in {self.registration_date}; detine {self.points} puncte'

    def search(self, string_to_search):
        for prop in [self.full_name, self.ssn, str(self.registration_date), str(self.birth_day)]:
            if string_to_search in prop:
                return True
        return False
